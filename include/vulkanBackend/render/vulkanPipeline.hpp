#pragma once

#include <vulkan/vulkan.hpp>
#include <optional>

#include "vulkanBackend/vulkanShader.hpp"

class VulkanSwapchain;

namespace rc
{
    class Shader;
}

class VulkanPipeline
{
public:
    void init(const VulkanSwapchain& swapchain, VkDevice device, VkDescriptorSetLayout materialSetLayout, VkRenderPass renderPass);
    void recreate(const VulkanSwapchain& swapchain, VkDevice device, VkRenderPass renderPass); // for graphics pipeline. Can be a bad idea

    void cleanup(VkDevice device);

    VkPipeline createPipeline(const VulkanSwapchain& swapchain, 
        VkDevice device, VkRenderPass renderPass,
        VkPrimitiveTopology topology, VkPolygonMode polygonMode);

    void setVertexShader(const rc::Shader& vertex);
    void setFragmentShader(const rc::Shader& frag);

    const VkDescriptorSetLayout& getDescriptorSetLayout() const;
    VkPipeline& getGraphicsPipeline();
    const VkPipelineLayout& getPipelineLayout() const;

private:
    VkPipelineShaderStageCreateInfo vertexStage{};
    VkPipelineShaderStageCreateInfo fragmentStage{};

    VkDescriptorSetLayout descriptorSetLayout;
    VkPipelineLayout pipelineLayout;

    VkPipeline graphicsPipeline;

    void createDescriptorSetLayout(VkDevice device);
};