#pragma once

#include <vulkan/vulkan.hpp>
#include <vector>

class VulkanDevice;
class VulkanSwapchain;

class FramebufferManager
{
public:
    void init(const VulkanDevice& vDevice, const VulkanSwapchain& swapchain, VkRenderPass renderPass);
    void cleanup(VkDevice device);

    const std::vector<VkFramebuffer>& getFramebuffers() const;

private:
    std::vector<VkFramebuffer> framebuffers;
};