#pragma once

#include <vulkan/vulkan.hpp>

class VulkanDevice;
class VulkanSwapchain;

class VulkanRenderPass
{
public:
    void init(const VulkanDevice& vDevice, const VulkanSwapchain& swapchain);
    void cleanup(VkDevice device);

    const VkRenderPass& getRenderPass() const;

private:
    VkRenderPass renderPass;
};