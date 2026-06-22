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

#include "RenderCore/rcGeometry.hpp"

#include <filesystem>
#include <iostream>


namespace rc::Internal
{
    Window* gWindow = nullptr;
    Camera* gCamera = nullptr;

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

    void Init()
    {
        glfwInit();
    }

    void InitVulkan(Window& window)
    {
        Internal::gWindow = &window;

        context.init(window);
        device.init(context);
        swapchain.init(device, context, window);
        renderPass.init(device, swapchain);
        pipeline.init(device.getDevice());

        framebuffers.init(device, swapchain, renderPass.getRenderPass());
        commandBuffer.init(device);
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
            std::cout << "Result: " << needResize << "\n";

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

    Shader LoadShader(const std::string& path, ShaderType type)
    {
        std::filesystem::path exeDir = std::filesystem::canonical("/proc/self/exe").parent_path();
        std::filesystem::path fullPath = exeDir / path;

        switch (type)
        {
            case ShaderType::VERTEX:
                return Shader(fullPath.string(), device.getDevice(), VK_SHADER_STAGE_VERTEX_BIT);

            case ShaderType::FRAGMENT:
                return Shader(fullPath.string(), device.getDevice(), VK_SHADER_STAGE_FRAGMENT_BIT);

            default:
                throw std::invalid_argument("Unsupported shader type!");
        }
    }
}