#include "RenderCore/RenderCore.hpp"
#include "RenderCore/rcInternal.hpp" 

#include "vulkanBackend/vulkanContext.hpp"
#include "vulkanBackend/vulkanDevice.hpp"
#include "vulkanBackend/vulkanSwapchain.hpp"

#include "vulkanBackend/render/vulkanRenderPass.hpp"
#include "vulkanBackend/render/vulkanPipeline.hpp"
#include "vulkanBackend/framebufferManager.hpp"
#include "vulkanBackend/render/vulkanCommandBuffer.hpp"
#include "vulkanBackend/render/vulkanRenderer.hpp"  

#include "engine/materials/materialSystem.hpp"

#include <filesystem>

namespace rc::Internal
{
    Window* gWindow = nullptr;
    Camera* gCamera = nullptr;
    VulkanDevice* gVulkDevice = nullptr;
    VulkanCommandBuffer* gCmd = nullptr;
    MaterialSystem* gMaterialSystem = nullptr;

    bool currentKeys[GLFW_KEY_LAST] = {};
    bool previousKeys[GLFW_KEY_LAST] = {};
}

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

    MaterialSystem materialSystem;

    void Init()
    {
        glfwInit();
    }

    void InitVulkan(Window& window)
    {
        Internal::gWindow = &window;

        context.init(window);
        device.init(context);

        Internal::gVulkDevice = &device;

        swapchain.init(device, context, window);

        commandBuffer.init(device);
        Internal::gCmd = &commandBuffer;
        
        renderPass.init(device, swapchain);
        
        materialSystem.init(device, commandBuffer);
        Internal::gMaterialSystem = &materialSystem;

        pipeline.init(device.getDevice(), materialSystem.getMaterialLayout());

        framebuffers.init(device, swapchain, renderPass.getRenderPass());
        renderer.init(device, swapchain, framebuffers, renderPass, pipeline, commandBuffer);
    }

    void SetCamera(rc::Camera& camera)
    {
        renderer.setCamera(camera);

        Internal::gCamera = &camera;
    }

    void SetShaders(Shader vertex, Shader fragment)
    {   
        pipeline.setVertexShader(std::move(vertex));
        pipeline.setFragmentShader(std::move(fragment));

        pipeline.build(swapchain, device.getDevice(), renderPass.getRenderPass());
    }

    void Terminate()
    {
        materialSystem.cleanup(device.getDevice());

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
        bool needResize = Internal::gWindow->framebufferResized;

        if (needResize)
        {
            int width = 0, height = 0;
            glfwGetFramebufferSize(Internal::gWindow->getWindowHandle(), &width, &height);
            
            while (width == 0 || height == 0)
            {
                glfwWaitEvents();
                glfwGetFramebufferSize(Internal::gWindow->getWindowHandle(), &width, &height);
            }

            vkDeviceWaitIdle(device.getDevice());

            framebuffers.cleanup(device.getDevice());
            swapchain.cleanup(device.getDevice());

            swapchain.init(device, context, *Internal::gWindow); 
            framebuffers.init(device, swapchain, renderPass.getRenderPass());

            renderer.onSwapchainRecreated();

            if (Internal::gCamera)
                Internal::gCamera->onResize(width, height);

            Internal::gWindow->framebufferResized = false;
        }

        renderer.beginFrame();

        Internal::UpdateInput();
    }

    void EndFrame()
    {
        renderer.endFrame();
    }

    void DrawObject(RenderItem& item)
    {
        renderer.draw(item);
    }
}