#pragma once

#include <vulkan/vulkan.hpp>
#include <optional>

#include "engine/shader.hpp"

class VulkanSwapchain;

class VulkanPipeline
{
public:
    void init(VkDevice device);
    void build(const VulkanSwapchain& swapchain, VkDevice device, VkRenderPass renderPass); // for graphics pipeline. Can be a bad idea

    void cleanup(VkDevice device);

    VkPipeline createPipeline(const VulkanSwapchain& swapchain, 
        VkDevice device, VkRenderPass renderPass,
        VkPrimitiveTopology topology, VkPolygonMode polygonMode);

    void setVertexShader(rc::Shader vertex);
    void setFragmentShader(rc::Shader frag);

    const VkDescriptorSetLayout& getDescriptorSetLayout() const;
    VkPipeline& getGraphicsPipeline();
    const VkPipelineLayout& getPipelineLayout() const;

private:
    std::optional<rc::Shader> vertexShader;
    std::optional<rc::Shader> fragmentShader;

    VkDescriptorSetLayout descriptorSetLayout;
    VkPipelineLayout pipelineLayout;

    VkPipeline graphicsPipeline;

    void createDescriptorSetLayout(VkDevice device);
};