#include "engine/materialSystem.hpp"
#include "vulkanBackend/vulkanTexture.hpp"
#include "RenderCore/core/rcTexture2D.hpp"
#include "vulkanBackend/vulkanDevice.hpp"

void MaterialSystem::init(VulkanDevice& vDevice, const VulkanCommandBuffer& cmd)
{
    this->vDevice = &vDevice;

    this->defaultTex = std::make_unique<rc::Texture2D>();
    this->defaultTex->handle->createWhitePixel(vDevice, cmd); 

    createMaterialDescriptorLayout();
    createMaterialDescriptorPool();
}

void MaterialSystem::cleanup(VkDevice device)
{
    vDevice = nullptr;

    defaultTex.reset();

    if (materialPool != VK_NULL_HANDLE) vkDestroyDescriptorPool(device, materialPool, nullptr);
    if (matLayout != VK_NULL_HANDLE) vkDestroyDescriptorSetLayout(device, matLayout, nullptr);
    
    // allocatedMaterials.clear();
}

void MaterialSystem::createMaterial(rc::Material& mat, rc::Color color, rc::Texture2D* texture)
{
    mat.color = color;
    mat.texture = texture;

    VkDescriptorSetAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    allocInfo.descriptorPool = materialPool;
    allocInfo.descriptorSetCount = 1;
    allocInfo.pSetLayouts = &matLayout;

    VkDescriptorSet descriptorSet;

    if (vkAllocateDescriptorSets(vDevice->getDevice(), &allocInfo, &descriptorSet) != VK_SUCCESS)
        throw std::runtime_error("Cannot allocate descriptor set for material!");

    mat.handle = reinterpret_cast<uintptr_t>(descriptorSet);

    rc::Texture2D* textureToBind = texture ? texture : defaultTex.get();

    VkDescriptorImageInfo imageInfo{};
    imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    imageInfo.imageView = textureToBind->handle->getImageView();
    imageInfo.sampler = textureToBind->handle->getSampler();

    VkWriteDescriptorSet descriptorWrite{};
    descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    descriptorWrite.dstSet = reinterpret_cast<VkDescriptorSet>(mat.handle);;
    descriptorWrite.dstBinding = 0;
    descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    descriptorWrite.descriptorCount = 1;
    descriptorWrite.pImageInfo = &imageInfo;

    vkUpdateDescriptorSets(vDevice->getDevice(), 1, &descriptorWrite, 0, nullptr);
}

void MaterialSystem::destroyMaterial(rc::Material& material)
{  
    VkDescriptorSet descriptorSet = reinterpret_cast<VkDescriptorSet>(material.handle);

    if (descriptorSet != VK_NULL_HANDLE)
        vkFreeDescriptorSets(vDevice->getDevice(), materialPool, 1, &descriptorSet);
}

VkDescriptorSetLayout MaterialSystem::getMaterialLayout() const
{
    return matLayout;
}

void MaterialSystem::createMaterialDescriptorLayout()
{   
    VkDescriptorSetLayoutBinding layoutBinding{};
    layoutBinding.binding = 0;
    layoutBinding.descriptorCount = 1;
    layoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    layoutBinding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;
    layoutBinding.pImmutableSamplers = nullptr;

    VkDescriptorSetLayoutCreateInfo layoutInfo{};
    layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    layoutInfo.bindingCount = 1;
    layoutInfo.pBindings = &layoutBinding;

    if (vkCreateDescriptorSetLayout(vDevice->getDevice(), &layoutInfo, nullptr, &matLayout) != VK_SUCCESS)
        throw std::runtime_error("Cannot create descriptor layout for material!");
}

void MaterialSystem::createMaterialDescriptorPool()
{
    VkDescriptorPoolSize poolSize{};
    poolSize.type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    poolSize.descriptorCount = 1000; // more than enough for now

    VkDescriptorPoolCreateInfo poolInfo{};
    poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    poolInfo.poolSizeCount = 1;
    poolInfo.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
    poolInfo.pPoolSizes = &poolSize;
    poolInfo.maxSets = 1000;

    if (vkCreateDescriptorPool(vDevice->getDevice(), &poolInfo, nullptr, &materialPool) != VK_SUCCESS)
        throw std::runtime_error("Failed to create material descriptor pool!");
}