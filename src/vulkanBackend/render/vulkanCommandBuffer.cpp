#include "vulkanBackend/render/vulkanCommandBuffer.hpp"
#include "vulkanBackend/vulkanDevice.hpp"
#include <stdexcept>

void VulkanCommandBuffer::init(const VulkanDevice& device)
{
    createCommandPool(device);
    createCommandBuffers(device.getDevice());
}

void VulkanCommandBuffer::cleanup(VkDevice device)
{
    vkDestroyCommandPool(device, commandPool, nullptr);
}

void VulkanCommandBuffer::reset(uint32_t index)
{
    vkResetCommandBuffer(commandBuffers[index], 0);
}

void VulkanCommandBuffer::begin(uint32_t index)
{
    VkCommandBufferBeginInfo beginInfo{};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    beginInfo.flags = 0;
    beginInfo.pInheritanceInfo = nullptr;

    if (vkBeginCommandBuffer(commandBuffers[index], &beginInfo) != VK_SUCCESS)
        throw std::runtime_error("Cannot begin recording command buffer!");
}

void VulkanCommandBuffer::end(uint32_t index)
{
    vkEndCommandBuffer(commandBuffers[index]);
}

const VkCommandPool& VulkanCommandBuffer::getCommandPool() const
{
    return commandPool;
}
    
const std::vector<VkCommandBuffer>& VulkanCommandBuffer::getCommandBuffers() const
{
    return commandBuffers;
}

void VulkanCommandBuffer::createCommandPool(const VulkanDevice& vDevice)
{
    QueueFamilyIndices indices = vDevice.getIndices();

    VkCommandPoolCreateInfo commandPoolInfo{};
    commandPoolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    commandPoolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    commandPoolInfo.queueFamilyIndex = indices.graphicsFamily.value();

    if (vkCreateCommandPool(vDevice.getDevice(), &commandPoolInfo, nullptr, &commandPool) != VK_SUCCESS)
    {
        throw std::runtime_error("Cannot create command pool!");
    }
}
    
void VulkanCommandBuffer::createCommandBuffers(VkDevice device)
{
    commandBuffers.resize(MAX_FRAMES_IN_FLIGHT);

    VkCommandBufferAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.commandPool = commandPool;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandBufferCount = static_cast<uint32_t>(commandBuffers.size());

    if (vkAllocateCommandBuffers(device, &allocInfo, commandBuffers.data()) != VK_SUCCESS)
    {
        throw std::runtime_error("Cannot create command buffer!");
    }
}