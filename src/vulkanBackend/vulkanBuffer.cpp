#include "vulkanBackend/vulkanBuffer.hpp"
#include "vulkanBackend/vulkanDevice.hpp"
#include "vulkanBackend/utils.hpp"
#include <stdexcept>
#include <cstring>

void VulkanBuffer::create(const VulkanDevice& vDevice, VkDeviceSize bufferSize, VkBufferUsageFlagBits bufferFlags, const void* data)
{
    VkBufferCreateInfo bufferInfo{};
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size = bufferSize;
    bufferInfo.usage = bufferFlags;
    bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    if (vkCreateBuffer(vDevice.getDevice(), &bufferInfo, nullptr, &buffer) != VK_SUCCESS)
    {
        throw std::runtime_error("Cannot create buffer!");
    }

    VkMemoryRequirements memRequirements;   
    vkGetBufferMemoryRequirements(vDevice.getDevice(), buffer, &memRequirements);

    VkMemoryAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocInfo.allocationSize = memRequirements.size;
    allocInfo.memoryTypeIndex = vkUtils::findMemoryType(vDevice.getPhysicalDevice(), memRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

    if (vkAllocateMemory(vDevice.getDevice(), &allocInfo, nullptr, &memory) != VK_SUCCESS)
    {
        throw std::runtime_error("Cannot allocate memory for vertex buffer!");
    }

    vkBindBufferMemory(vDevice.getDevice(), buffer, memory, 0);

    if (data != nullptr)
    {
        void* mapppedData;
        vkMapMemory(vDevice.getDevice(), memory, 0, bufferInfo.size, 0, &mapppedData);
        memcpy(mapppedData, data, (size_t) bufferInfo.size);
        vkUnmapMemory(vDevice.getDevice(), memory);
    }
}

void VulkanBuffer::cleanup(VkDevice device)
{
    vkDeviceWaitIdle(device); // NOT A GOOD IDEA

    if (buffer != VK_NULL_HANDLE)
        vkDestroyBuffer(device, buffer, nullptr);
    
    vkFreeMemory(device, memory, nullptr);
}
