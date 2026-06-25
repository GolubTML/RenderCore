#include "RenderCore/core/rcWindow.hpp"
#include "RenderCore/rcTypes.hpp"

namespace rc
{
    Window::Window(const WindowDesc& desc)
    {
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

        bool resize = desc.resizable == true ? GLFW_TRUE : GLFW_FALSE;

        glfwWindowHint(GLFW_RESIZABLE, resize);

        handle = glfwCreateWindow(desc.width, desc.height, desc.title.c_str(), nullptr, nullptr);

        glfwSetWindowUserPointer(handle, this);

        glfwSetFramebufferSizeCallback(handle, [](GLFWwindow* window, int width, int height)
        {
            auto appWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

            appWindow->framebufferResized = true;
        });
    }

    void Window::Terminate()
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