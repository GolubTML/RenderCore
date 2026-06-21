#pragma once

#include <vulkan/vulkan.hpp>
#include <vector>
#include <cstdint>

class VulkanDevice;

constexpr static const int MAX_FRAMES_IN_FLIGHT = 2;

class VulkanCommandBuffer
{
public:
    void init(const VulkanDevice& device);
    void cleanup(VkDevice device);

    void reset(uint32_t index);
    void begin(uint32_t index);
    void end(uint32_t index);

    const VkCommandPool& getCommandPool() const;
    const std::vector<VkCommandBuffer>& getCommandBuffers() const;

private:
    VkCommandPool commandPool;
    std::vector<VkCommandBuffer> commandBuffers;

    void createCommandPool(const VulkanDevice& device);
    void createCommandBuffers(VkDevice device);
};