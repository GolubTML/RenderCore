#include "RenderCore/rcInternal.hpp"

namespace rc::Internal
{
    void UpdateInput()
    {
        for (int i = 0; i < GLFW_KEY_LAST; ++i)
        {
            previousKeys[i] = currentKeys[i];
            currentKeys[i] = glfwGetKey(gWindow, i) == GLFW_PRESS;
        }
    }
}