#pragma once

#include <vulkan/vulkan.hpp>

class VulkanSwapchain;

class VulkanPipeline
{
public:
    void init(const VulkanSwapchain& swapchain, VkDevice device, VkRenderPass renderPass);
    void cleanup(VkDevice device);

    VkPipeline createPipeline(const VulkanSwapchain& swapchain, 
        VkDevice device, VkRenderPass renderPass, 
        const std::string& vertPath, const std::string& fragPath,
        VkPrimitiveTopology topology, VkPolygonMode polygonMode);
    
    const VkDescriptorSetLayout& getDescriptorSetLayout() const;
    VkPipeline& getGraphicsPipeline();
    const VkPipelineLayout& getPipelineLayout() const;

private:
    VkDescriptorSetLayout descriptorSetLayout;
    VkPipelineLayout pipelineLayout;

    VkPipeline graphicsPipeline;

    void createDescriptorSetLayout(VkDevice device);
};