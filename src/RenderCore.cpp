#include "RenderCore.hpp"
#include <GLFW/glfw3.h>

namespace rc
{
    VulkanContext context;
    VulkanDevice device;
    VulkanSwapchain swapchain;
    VulkanRenderPass renderPass;
    VulkanPipeline pipeline;
    FramebufferManager framebuffers;
    VulkanCommandBuffer commandBuffer;
    VulkanRenderer renderer;

    void Init()
    {
        glfwInit();
    }

    void InitVulkan(Window& window)
    {
        context.init(window);
        device.init(context);
        swapchain.init(device, context, window);
        renderPass.init(device, swapchain);
        pipeline.init(swapchain, device.getDevice(), renderPass.getRenderPass());

        framebuffers.init(device, swapchain, renderPass.getRenderPass());
        commandBuffer.init(device);
        renderer.init(device, swapchain, framebuffers, renderPass, pipeline, commandBuffer);
    }

    void Terminate()
    {
        renderer.cleanup(device.getDevice());
        commandBuffer.cleanup(device.getDevice());
        framebuffers.cleanup(device.getDevice());
        pipeline.cleanup(device.getDevice());
        renderPass.cleanup(device.getDevice());
        swapchain.cleanup(device.getDevice());

        device.cleanup();

        context.cleanup();

        glfwTerminate();
    }

    void ClearColor(float r, float g, float b)
    {
        renderer.setClearValues(r, g, b);
    }

    void BeginFrame()
    {
        renderer.beginFrame();
    }

    void EndFrame()
    {
        renderer.endFrame();
    }

    void DrawTest()
    {
        renderer.drawTriangle();
    }
}