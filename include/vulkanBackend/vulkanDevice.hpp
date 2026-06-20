#pragma once

#include <vulkan/vulkan.hpp>
#include <optional>

struct QueueFamilyIndices 
{
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;

    bool isComplete()
    {
        return graphicsFamily.has_value() && presentFamily.has_value();
    }
};

class VulkanContext;

class VulkanDevice
{
public:
    void init(VulkanContext& context);
    void cleanup();

    const VkPhysicalDevice& getPhysicalDevice() const;
    const VkDevice& getDevice() const;
    const QueueFamilyIndices& getIndices() const;

private:
    std::vector<const char*> deviceExtensions;

    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    VkDevice device = VK_NULL_HANDLE;

    QueueFamilyIndices indices;

    void createDevice(VkSurfaceKHR surface);
    void pickPhysicalDevice(VulkanContext& context);

    bool isDeviceSuitable(VkPhysicalDevice device, VkSurfaceKHR surface);
    bool chechDeviceExtensionSupport(VkPhysicalDevice device);
    
    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR surface);
};