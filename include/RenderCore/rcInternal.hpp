#pragma once

#include <GLFW/glfw3.h>

namespace rc
{
    class Window;
    class Camera;
}

class VulkanDevice;
class VulkanCommandBuffer;
class MaterialSystem;

namespace rc::Internal
{
    extern Window* gWindow;
    extern Camera* gCamera;
    extern VulkanDevice* gVulkDevice;
    extern VulkanCommandBuffer* gCmd;
    extern MaterialSystem* gMaterialSystem;

    extern bool currentKeys[GLFW_KEY_LAST];
    extern bool previousKeys[GLFW_KEY_LAST];

    void UpdateInput();
}