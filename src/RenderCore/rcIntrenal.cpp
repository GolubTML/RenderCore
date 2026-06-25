#include "RenderCore/rcInternal.hpp"

#include "RenderCore/core/rcWindow.hpp"

namespace rc::Internal
{
    void UpdateInput()
    {
        for (int i = 0; i < GLFW_KEY_LAST; ++i)
        {
            previousKeys[i] = currentKeys[i];
            currentKeys[i] = glfwGetKey(gWindow->getWindowHandle(), i) == GLFW_PRESS;
        }
    }
}