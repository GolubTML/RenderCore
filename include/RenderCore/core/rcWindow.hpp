#pragma once

#include <string>
#include <GLFW/glfw3.h>

namespace rc
{
    struct WindowDesc;

    class Window
    {
    public:
        bool framebufferResized = false;

        Window(const WindowDesc& desc);
        ~Window() = default;

        void Terminate();

        bool ShouldClose();
        void PollEvents();

        GLFWwindow* getWindowHandle() const;

    private:
        GLFWwindow* handle = nullptr; // window
    };
}