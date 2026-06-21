#include "RenderCore/RenderCore.hpp"
#include <GLFW/glfw3.h>

#include "vulkanBackend/vulkanContext.hpp"
#include "vulkanBackend/vulkanDevice.hpp"
#include "vulkanBackend/vulkanSwapchain.hpp"

#include "vulkanBackend/render/vulkanRenderPass.hpp"
#include "vulkanBackend/render/vulkanPipeline.hpp"
#include "vulkanBackend/framebufferManager.hpp"
#include "vulkanBackend/render/vulkanCommandBuffer.hpp"
#include "vulkanBackend/render/vulkanRenderer.hpp"  

#include "RenderCore/rcGeometry.hpp"

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

    void SetCamera(rc::Camera& camera)
    {
        renderer.setCamera(camera);
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

    void DrawObject(RenderItem& item)
    {
        renderer.draw(item);
    }

    void DestroyObject(RenderItem& item)
    {
        item.mesh.cleanup(device.getDevice());
    }

    RenderItem CreateRectangle(const glm::vec2& position, float w, float h, const Color& color)
    {
        auto data = Geometry::CreateRectangleData(w, h, color);

        RenderItem item 
        {
            .mesh = Mesh{},
            .transform = {glm::vec3(position.x, position.y, 0.f), glm::vec3{0.f}, glm::vec3{1.f}}
        };

        item.mesh.create(device, data.first, data.second);

        return item;
    }
}