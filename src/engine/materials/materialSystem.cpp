#include "engine/materials/materialSystem.hpp"
#include "engine/materials/texture.hpp"
#include "vulkanBackend/vulkanDevice.hpp"

void MaterialSystem::init(VulkanDevice& vDevice, const VulkanCommandBuffer& cmd)
{
    this->vDevice = &vDevice;

    this->defaultTex = new rc::Texture2D();
    this->defaultTex->createWhitePixel(vDevice, cmd); 

    createMaterialDescriptorLayout();
    createMaterialDescriptorPool();
}

void MaterialSystem::cleanup(VkDevice device)
{
    vDevice = nullptr;

    defaultTex->cleanup(device);

    if (materialPool != VK_NULL_HANDLE) vkDestroyDescriptorPool(device, materialPool, nullptr);
    if (matLayout != VK_NULL_HANDLE) vkDestroyDescriptorSetLayout(device, matLayout, nullptr);
    
    allocatedMaterials.clear();
}

rc::Material* MaterialSystem::createMaterial(rc::Texture2D* texture, rc::Color color)
{
    auto mat = std::make_unique<rc::Material>();
    mat->color = color;
    mat->texture = texture;

    VkDescriptorSetAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    allocInfo.descriptorPool = materialPool;
    allocInfo.descriptorSetCount = 1;
    allocInfo.pSetLayouts = &matLayout;

    if (vkAllocateDescriptorSets(vDevice->getDevice(), &allocInfo, &mat->descriptorSet) != VK_SUCCESS)
        throw std::runtime_error("Cannot allocate descriptor set for material!");

    rc::Texture2D* textureToBind = texture ? texture : defaultTex;

    VkDescriptorImageInfo imageInfo{};
    imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    imageInfo.imageView = textureToBind->getImageView();
    imageInfo.sampler = textureToBind->getSampler();

    VkWriteDescriptorSet descriptorWrite{};
    descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    descriptorWrite.dstSet = mat->descriptorSet;
    descriptorWrite.dstBinding = 0;
    descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    descriptorWrite.descriptorCount = 1;
    descriptorWrite.pImageInfo = &imageInfo;

    vkUpdateDescriptorSets(vDevice->getDevice(), 1, &descriptorWrite, 0, nullptr);

    rc::Material* rawPtr = mat.get();
    allocatedMaterials.push_back(std::move(mat));

    return rawPtr;
}

void MaterialSystem::destroyMaterial(rc::Material* material)
{
    if (!material) throw std::runtime_error("Invalide material pointer!");
    
    if (material->descriptorSet != VK_NULL_HANDLE)
        vkFreeDescriptorSets(vDevice->getDevice(), materialPool, 1, &material->descriptorSet);

    if (material->texture && material->texture != defaultTex)
        material->texture->cleanup(vDevice->getDevice());

    auto it = std::find_if(allocatedMaterials.begin(), allocatedMaterials.end(),
        [material](const std::unique_ptr<rc::Material>& mat) {
            return mat.get() == material;
        });

    if (it != allocatedMaterials.end()) {
        allocatedMaterials.erase(it);
    }
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