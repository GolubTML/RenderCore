#pragma once

#include "RenderCore/core/rcMaterial.hpp"
#include <vulkan/vulkan.hpp>
#include <vector>
#include <memory>

class VulkanDevice;
class VulkanCommandBuffer;

class MaterialSystem
{
public:
    void init(VulkanDevice& vDevice, const VulkanCommandBuffer& cmd);
    void cleanup(VkDevice device);

    void createMaterial(rc::Material& mat, rc::Color color, rc::Texture2D* texture = nullptr);
    void destroyMaterial(rc::Material& material);

    VkDescriptorSetLayout getMaterialLayout() const;

private:
    VulkanDevice* vDevice = nullptr;
    VkDescriptorSetLayout matLayout = VK_NULL_HANDLE; 
    VkDescriptorPool materialPool = VK_NULL_HANDLE;

    std::unique_ptr<rc::Texture2D> defaultTex = nullptr;

    void createMaterialDescriptorLayout();
    void createMaterialDescriptorPool();
};