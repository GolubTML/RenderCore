#pragma once

#include "engine/window.hpp"

#include "vulkanBackend/vulkanContext.hpp"
#include "vulkanBackend/vulkanDevice.hpp"
#include "vulkanBackend/vulkanSwapchain.hpp"

#include "vulkanBackend/render/vulkanRenderPass.hpp"
#include "vulkanBackend/render/vulkanPipeline.hpp"
#include "vulkanBackend/framebufferManager.hpp"
#include "vulkanBackend/render/vulkanCommandBuffer.hpp"
#include "vulkanBackend/render/vulkanRenderer.hpp"  

namespace rc
{
    void Init();
    void InitVulkan(Window& window);

    void Terminate();

    void BeginFrame();
    void EndFrame();
}