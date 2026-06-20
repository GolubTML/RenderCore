#pragma once

#include <vulkan/vulkan.hpp>

class VulkanDevice;

class VulkanBuffer
{
public:
    VkBuffer buffer = VK_NULL_HANDLE;
    VkDeviceMemory memory;

    void create(const VulkanDevice& vDevice, VkDeviceSize bufferSize, VkBufferUsageFlagBits bufferFlags, const void* data);
    void cleanup(VkDevice device);
};