#pragma once

#include <vulkan/vulkan.hpp>
#include <vector>
#include "engine/window.hpp"

struct SwapChainSupportDetails
{
    VkSurfaceCapabilitiesKHR capabilities;
    
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};

SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device, VkSurfaceKHR surface);

class VulkanContext;
class VulkanDevice;

class VulkanSwapchain
{
public:
    void init(const VulkanDevice& vDevice, const VulkanContext& context, const rc::Window& window);
    void cleanup(VkDevice device);
    
    const VkSwapchainKHR& getSwapchain() const;

    const std::vector<VkImage>& getSwapChainImages() const;
    const std::vector<VkImageView>& getSwapChainImageViews() const;
    const VkFormat& getSwapchainImageFormat() const;

    const VkExtent2D& getSwapchainExtent() const;
    const VkImageView& getDepthImageView() const;

private:
    VkSwapchainKHR swapChain;
    std::vector<VkImage> swapChainImages;
    std::vector<VkImageView> swapChainImageViews;
    VkFormat swapChainImageFormat;
    VkExtent2D swapChainExtent;

    // z buffer
    VkImage depthImage = VK_NULL_HANDLE;
    VkDeviceMemory depthImageMemory = VK_NULL_HANDLE;
    VkImageView depthImageView = VK_NULL_HANDLE;

    const VkFormat depthFormat = VK_FORMAT_D32_SFLOAT;

    void createSwapchain(const VulkanDevice& vDevice, VkSurfaceKHR surface, const rc::Window& window);
    void createImageViews(VkDevice device);
    void createDepthResources(const VulkanDevice& vDevice);

    // helpers
    VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
    VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
    VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities, const rc::Window& window);
};