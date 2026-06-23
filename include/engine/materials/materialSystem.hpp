#pragma once

#include "engine/materials/material.hpp"
#include <vector>
#include <memory>

class VulkanDevice;
class VulkanCommandBuffer;

class MaterialSystem
{
public:
    void init(VulkanDevice& vDevice, const VulkanCommandBuffer& cmd);
    void cleanup(VkDevice device);

    rc::Material* createMaterial(rc::Texture2D* texture, rc::Color color);
    void destroyMaterial(rc::Material* material);

    VkDescriptorSetLayout getMaterialLayout() const;

private:
    VulkanDevice* vDevice = nullptr;
    VkDescriptorSetLayout matLayout = VK_NULL_HANDLE; 
    VkDescriptorPool materialPool = VK_NULL_HANDLE;

    rc::Texture2D* defaultTex = nullptr;
    std::vector<std::unique_ptr<rc::Material>> allocatedMaterials;

    void createMaterialDescriptorLayout();
    void createMaterialDescriptorPool();
};