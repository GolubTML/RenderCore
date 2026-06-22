#include "vulkanBackend/render/vulkanRenderer.hpp"
#include "vulkanBackend/vulkanDevice.hpp"
#include "vulkanBackend/vulkanSwapchain.hpp"
#include "vulkanBackend/framebufferManager.hpp"
#include "vulkanBackend/render/vulkanPipeline.hpp"
#include "vulkanBackend/render/vulkanRenderPass.hpp"
#include "vulkanBackend/render/vulkanCommandBuffer.hpp"
#include "vulkanBackend/types.hpp"
#include "engine/camera/camera.hpp"
#include "engine/renderItem.hpp"

void VulkanRenderer::init(VulkanDevice& device, 
        VulkanSwapchain& Swapchain,
        FramebufferManager& Framebuffers,
        VulkanRenderPass& RenderPass,
        VulkanPipeline& Pipeline,
        VulkanCommandBuffer& Cmd)
{
    vDevice = &device;
    swapchain = &Swapchain;
    framebuffers = &Framebuffers;
    renderPass = &RenderPass;
    pipeline = &Pipeline;
    cmd = &Cmd;

    createSyncObjects();

    createUniformBuffers();

    createDescriptorPool();
    createDescriptorSet();
}

void VulkanRenderer::cleanup(VkDevice device)
{
    vDevice = nullptr;
    swapchain = nullptr;
    framebuffers = nullptr;
    renderPass = nullptr;
    pipeline = nullptr;
    cmd = nullptr;

    if (cameraPtr)
        cameraPtr = nullptr;

    vkDeviceWaitIdle(device);

    for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) 
    {
        vkDestroySemaphore(device, imageAvailableSemaphores[i], nullptr);

        vkDestroyFence(device, inFlightFences[i], nullptr);

        uniformBuffers[i].cleanup(device);
    }

    for (size_t i = 0; i < renderFinishedSemaphores.size(); i++)
    {
        vkDestroySemaphore(device, renderFinishedSemaphores[i], nullptr);
    }

    vkDestroyDescriptorPool(device, descriptorPool, nullptr);
}

void VulkanRenderer::onSwapchainRecreated()
{
    imagesInFlight.assign(swapchain->getSwapChainImages().size(), VK_NULL_HANDLE);

    for (auto& sem : renderFinishedSemaphores)
        vkDestroySemaphore(vDevice->getDevice(), sem, nullptr);

    renderFinishedSemaphores.resize(swapchain->getSwapChainImages().size());

    VkSemaphoreCreateInfo semaphoreInfo{};
    semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
    
    for (auto& sem : renderFinishedSemaphores)
    {
        if (vkCreateSemaphore(vDevice->getDevice(), &semaphoreInfo, nullptr, &sem) != VK_SUCCESS)
            throw std::runtime_error("Cannot recreate semaphores after resize!");
    }
}

void VulkanRenderer::setCamera(rc::Camera& c)
{
    cameraPtr = &c;
}

void VulkanRenderer::setClearValues(float r, float g, float b)
{
    clearValues[0].color = {r, g, b, 1.f};
    clearValues[1].depthStencil = {1.f, 0};
}

void VulkanRenderer::beginFrame()
{
    vkWaitForFences(vDevice->getDevice(), 1, &inFlightFences[currentFrame], VK_TRUE, UINT64_MAX);

    vkAcquireNextImageKHR(vDevice->getDevice(), swapchain->getSwapchain(), UINT64_MAX, imageAvailableSemaphores[currentFrame], VK_NULL_HANDLE, &currentImageIndex);

    if (imagesInFlight[currentImageIndex] != VK_NULL_HANDLE)
        vkWaitForFences(vDevice->getDevice(), 1, &imagesInFlight[currentImageIndex], VK_TRUE, UINT64_MAX);

    imagesInFlight[currentImageIndex] = inFlightFences[currentFrame];

    vkResetFences(vDevice->getDevice(), 1, &inFlightFences[currentFrame]);
    updateUniformBuffer();

    cmd->begin(currentFrame);

    VkRenderPassBeginInfo beginInfo{};
    beginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    beginInfo.renderPass = renderPass->getRenderPass();
    beginInfo.framebuffer = framebuffers->getFramebuffers()[currentImageIndex];
    beginInfo.renderArea.offset = {0,0};
    beginInfo.renderArea.extent = swapchain->getSwapchainExtent();

    beginInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
    beginInfo.pClearValues = clearValues.data();

    vkCmdBeginRenderPass(cmd->getCommandBuffers()[currentFrame], &beginInfo, VK_SUBPASS_CONTENTS_INLINE);

    VkViewport viewport{};
    viewport.x = 0.0f;
    viewport.y = 0.0f;
    viewport.width = (float)swapchain->getSwapchainExtent().width;
    viewport.height = (float)swapchain->getSwapchainExtent().height;
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;

    vkCmdSetViewport(cmd->getCommandBuffers()[currentFrame], 0, 1, &viewport);

    VkRect2D scissor{};
    scissor.offset = {0, 0};
    scissor.extent = swapchain->getSwapchainExtent();

    vkCmdSetScissor(cmd->getCommandBuffers()[currentFrame], 0, 1, &scissor);
}
    
void VulkanRenderer::endFrame()
{
    VkCommandBuffer commandBuffer = cmd->getCommandBuffers()[currentFrame];

    vkCmdEndRenderPass(commandBuffer);

    cmd->end(currentFrame);

    VkSubmitInfo submitInfo{};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

    VkSemaphore waitSemaphores[] = {imageAvailableSemaphores[currentFrame]};
    VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
    
    submitInfo.waitSemaphoreCount = 1;
    submitInfo.pWaitSemaphores = waitSemaphores;
    submitInfo.pWaitDstStageMask = waitStages;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &cmd->getCommandBuffers()[currentFrame];

    VkSemaphore signalSemaphores[] = {renderFinishedSemaphores[currentImageIndex]};

    submitInfo.signalSemaphoreCount = 1;
    submitInfo.pSignalSemaphores = signalSemaphores;

    if (vkQueueSubmit(vDevice->getGraphicsQueue(), 1, &submitInfo, inFlightFences[currentFrame]) != VK_SUCCESS) 
        throw std::runtime_error("failed to submit draw command buffer!");

    VkPresentInfoKHR presentInfo{};
    presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    presentInfo.waitSemaphoreCount = 1;
    presentInfo.pWaitSemaphores = signalSemaphores;

    VkSwapchainKHR swapChains[] = {swapchain->getSwapchain()};
    presentInfo.swapchainCount = 1;
    presentInfo.pSwapchains = swapChains;
    presentInfo.pImageIndices = &currentImageIndex;

    presentInfo.pResults = nullptr;

    vkQueuePresentKHR(vDevice->getPresentQueue(), &presentInfo);

    currentFrame = (currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
    
    // if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR)
    //     return true;
    // else if(result != VK_SUCCESS)
    //     throw std::runtime_error("Failed to present frame!");

    // return false;
}

void VulkanRenderer::draw(rc::RenderItem& item)
{
    auto cmdBuf = cmd->getCommandBuffers()[currentFrame];

    vkCmdBindPipeline(cmdBuf, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline->getGraphicsPipeline());

    vkCmdBindDescriptorSets(cmdBuf, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline->getPipelineLayout(), 0, 1, &descriptorSets[currentFrame], 0, nullptr);

    glm::mat4 model = item.transform.getModelMatrix();
    vkCmdPushConstants(cmdBuf, pipeline->getPipelineLayout(), VK_SHADER_STAGE_VERTEX_BIT, 0, sizeof(glm::mat4), &model);

    item.mesh.draw(*cmd, currentFrame);
}

void VulkanRenderer::createDescriptorPool()
{
    std::array<VkDescriptorPoolSize, 2> poolSizes{};
    poolSizes[0].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    poolSizes[0].descriptorCount = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT);
    poolSizes[1].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    poolSizes[1].descriptorCount = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT);

    VkDescriptorPoolCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    createInfo.poolSizeCount = static_cast<uint32_t>(poolSizes.size());
    createInfo.pPoolSizes = poolSizes.data();
    createInfo.maxSets = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT);

    if (vkCreateDescriptorPool(vDevice->getDevice(), &createInfo, nullptr, &descriptorPool) != VK_SUCCESS)
    {
        throw std::runtime_error("Cannot create descriptor pool!");
    }
}

void VulkanRenderer::createDescriptorSet()
{
    std::vector<VkDescriptorSetLayout> layouts(MAX_FRAMES_IN_FLIGHT, pipeline->getDescriptorSetLayout());

    VkDescriptorSetAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    allocInfo.descriptorPool = descriptorPool;
    allocInfo.descriptorSetCount = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT);
    allocInfo.pSetLayouts = layouts.data();

    descriptorSets.resize(MAX_FRAMES_IN_FLIGHT);

    if (vkAllocateDescriptorSets(vDevice->getDevice(), &allocInfo, descriptorSets.data()) != VK_SUCCESS)
    {
        throw std::runtime_error("Cannot allocate description set!");
    }

    for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; ++i)
    {
        VkDescriptorBufferInfo bufferInfo{};
        bufferInfo.buffer = uniformBuffers[i].buffer;
        bufferInfo.offset = 0;
        bufferInfo.range = sizeof(UniformBufferObject);

        VkWriteDescriptorSet write{};

        write.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        write.dstSet = descriptorSets[i];
        write.dstBinding = 0;
        write.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        write.descriptorCount = 1;
        write.pBufferInfo = &bufferInfo;

        vkUpdateDescriptorSets(vDevice->getDevice(), 1, &write, 0, nullptr);
    }
}

void VulkanRenderer::createUniformBuffers()
{
    VkDeviceSize bufferSize = sizeof(UniformBufferObject);

    uniformBuffers.resize(MAX_FRAMES_IN_FLIGHT);
    uniformBuffersMapped.resize(MAX_FRAMES_IN_FLIGHT);

    for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; ++i)
    {
        uniformBuffers[i].create(*vDevice, bufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, nullptr);
            
        VkResult res = vkMapMemory(vDevice->getDevice(),
            uniformBuffers[i].memory,
            0, bufferSize, 0,
            &uniformBuffersMapped[i]);

        if (res != VK_SUCCESS)
            throw std::runtime_error("vkMapMemory failed!");
    }
}

void VulkanRenderer::updateUniformBuffer()
{
    if (cameraPtr == nullptr)
        throw std::runtime_error("Camera is not defined! Please, use rc::SetCamera(Camera)!");

    UniformBufferObject ubo{};

    ubo.view = cameraPtr->getView();

    ubo.proj = cameraPtr->getProjection();

    memcpy(uniformBuffersMapped[currentFrame], &ubo, sizeof(ubo));
}

void VulkanRenderer::createSyncObjects()
{   
    imageAvailableSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
    renderFinishedSemaphores.resize(swapchain->getSwapChainImages().size());

    imagesInFlight.resize(swapchain->getSwapChainImages().size(), VK_NULL_HANDLE);
    inFlightFences.resize(MAX_FRAMES_IN_FLIGHT);

    VkSemaphoreCreateInfo semaphoreInfo{};
    semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

    VkFenceCreateInfo fenceInfo{};
    fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

    for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; ++i)
    {
        if (vkCreateSemaphore(vDevice->getDevice(), &semaphoreInfo, nullptr, &imageAvailableSemaphores[i]) != VK_SUCCESS 
        || vkCreateFence(vDevice->getDevice(), &fenceInfo, nullptr, &inFlightFences[i]) != VK_SUCCESS)
        {
            throw std::runtime_error("Cannot create semaphores!");
        }
    }

    for (size_t i = 0; i < renderFinishedSemaphores.size(); ++i)
    {
        if (vkCreateSemaphore(vDevice->getDevice(), &semaphoreInfo, nullptr, &renderFinishedSemaphores[i]) != VK_SUCCESS)
        {
            throw std::runtime_error("Cannot create render finished semaphores!");
        }
    }
}