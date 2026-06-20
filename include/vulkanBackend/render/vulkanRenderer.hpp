#pragma once

#include "vulkanBackend/vulkanBuffer.hpp"

class VulkanDevice;
class VulkanSwapchain;
class FramebufferManager;
class VulkanPipeline;
class VulkanCommandBuffer;
class VulkanRenderPass;

namespace rc
{
    class Camera;
    class RenderItem;
}

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

    void setCamera(rc::Camera& c);
    void setClearValues(float r, float g, float b);

    uint32_t beginFrame();
    void endFrame();

    void draw(rc::RenderItem& item);

private:
    VulkanDevice* vDevice = nullptr;
    VulkanSwapchain* swapchain = nullptr;
    FramebufferManager* framebuffers = nullptr;
    VulkanRenderPass* renderPass = nullptr;
    VulkanPipeline* pipeline = nullptr;
    VulkanCommandBuffer* cmd = nullptr;

    std::array<VkClearValue, 2> clearValues{};

    std::vector<VkSemaphore> imageAvailableSemaphores;
    std::vector<VkSemaphore> renderFinishedSemaphores;
    std::vector<VkFence> inFlightFences;

    std::vector<VulkanBuffer> uniformBuffers;
    std::vector<void*> uniformBuffersMapped;

    VkDescriptorPool descriptorPool;
    std::vector<VkDescriptorSet> descriptorSets;

    uint32_t currentFrame = 0;
    uint32_t currentImageIndex = 0;

    rc::Camera* cameraPtr = nullptr;

    void createDescriptorPool();
    void createDescriptorSet();

    void createUniformBuffers();
    void updateUniformBuffer();

    void createSyncObjects();
};