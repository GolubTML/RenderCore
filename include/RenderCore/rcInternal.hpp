#pragma once

#include <GLFW/glfw3.h>

namespace rc::Internal
{
    extern GLFWwindow* gWindow;

    extern bool currentKeys[GLFW_KEY_LAST];
    extern bool previousKeys[GLFW_KEY_LAST];

    void UpdateInput();
}