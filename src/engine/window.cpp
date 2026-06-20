#include "engine/window.hpp"

namespace rc
{
    Window::Window(const WindowDesc& desc)
    {
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

        handle = glfwCreateWindow(desc.width, desc.height, desc.title.c_str(), nullptr, nullptr);
    }

    Window::~Window()
    {
        if (handle)
            glfwDestroyWindow(handle);
    }

    bool Window::ShouldClose()
    {
        return glfwWindowShouldClose(handle);
    }

    void Window::PollEvents()
    {
        return glfwPollEvents();
    }

    GLFWwindow* Window::getWindowHandle() const
    {
        return handle;
    }
}