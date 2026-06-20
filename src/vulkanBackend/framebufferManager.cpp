#include "vulkanBackend/framebufferManager.hpp"
#include "vulkanBackend/vulkanDevice.hpp"
#include "vulkanBackend/vulkanSwapchain.hpp"
#include <stdexcept>

void FramebufferManager::init(const VulkanDevice& vDevice, const VulkanSwapchain& swapchain, VkRenderPass renderPass)
{
    framebuffers.resize(swapchain.getSwapChainImageViews().size());

    for (size_t i = 0; i < swapchain.getSwapChainImageViews().size(); ++i)
    {
        VkImageView attachments[] = 
        { 
            swapchain.getSwapChainImageViews()[i],
            swapchain.getDepthImageView() 
        };

        VkFramebufferCreateInfo framebufferInfo{};
        framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        framebufferInfo.renderPass = renderPass;
        framebufferInfo.attachmentCount = 2;
        framebufferInfo.width = swapchain.getSwapchainExtent().width;
        framebufferInfo.height = swapchain.getSwapchainExtent().height;
        framebufferInfo.pAttachments = attachments;
        framebufferInfo.layers = 1;

        if (vkCreateFramebuffer(vDevice.getDevice(), &framebufferInfo, nullptr, &framebuffers[i]) != VK_SUCCESS)
        {
            throw std::runtime_error("Cannot create framebuffer for image view!");
        }
    }
}

void FramebufferManager::cleanup(VkDevice device)
{
    for (auto& frame : framebuffers) // idk how to name it
        vkDestroyFramebuffer(device, frame, nullptr);

    framebuffers.clear();
}

const std::vector<VkFramebuffer>& FramebufferManager::getFramebuffers() const
{
    return framebuffers;
}