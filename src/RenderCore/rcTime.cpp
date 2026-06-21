#include "RenderCore/rcTime.hpp"
#include <GLFW/glfw3.h>

namespace rc::Time
{
    float lastTime = 0.f;

    float GetTime()
    {
        return glfwGetTime(); // yeah
    }

    float GetDeltaTime()
    {
        float currentTime = glfwGetTime();

        float deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        return deltaTime;
    }
}