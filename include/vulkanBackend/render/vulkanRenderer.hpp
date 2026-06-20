#pragma once

#include "vulkanBackend/vulkanBuffer.hpp"

class VulkanDevice;
class VulkanSwapchain;
class FramebufferManager;
class VulkanPipeline;
class VulkanCommandBuffer;
class VulkanRenderPass;

class VulkanRenderer
{
public:
    void init(VulkanDevice& device, 
        VulkanSwapchain& Swapchain,
        FramebufferManager& Framebuffers,
        VulkanRenderPass& RenderPass,
        VulkanPipeline& Pipeline,
        VulkanCommandBuffer& Cmd);

    void cleanup(VkDevice device);

    uint32_t beginFrame();
    void endFrame();

private:
    VulkanDevice* vDevice = nullptr;
    VulkanSwapchain* swapchain = nullptr;
    FramebufferManager* framebuffers = nullptr;
    VulkanRenderPass* renderPass = nullptr;
    VulkanPipeline* pipeline = nullptr;
    VulkanCommandBuffer* cmd = nullptr;

    std::vector<VkSemaphore> imageAvailableSemaphores;
    std::vector<VkSemaphore> renderFinishedSemaphores;
    std::vector<VkFence> inFlightFences;

    std::vector<VulkanBuffer> uniformBuffers;
    std::vector<void*> uniformBuffersMapped;

    VkDescriptorPool descriptorPool;
    std::vector<VkDescriptorSet> descriptorSets;

    uint32_t currentFrame = 0;
    uint32_t currentImageIndex = 0;

    void createDescriptorPool();
    void createDescriptorSet();

    void createUniformBuffers();
    void updateUniformBuffer();

    void createSyncObjects();
    // record command buffer?
};