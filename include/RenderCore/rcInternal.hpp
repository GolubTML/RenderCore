#pragma once

#include <GLFW/glfw3.h>

namespace rc
{
    class Window;
    class Camera;
}

namespace rc::Internal
{
    extern Window* gWindow;
    extern Camera* gCamera;

    extern bool currentKeys[GLFW_KEY_LAST];
    extern bool previousKeys[GLFW_KEY_LAST];

    void UpdateInput();
}