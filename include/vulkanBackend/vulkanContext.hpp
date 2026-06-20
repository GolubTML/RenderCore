#pragma once

#include <vulkan/vulkan.hpp>
#include <vector>
#include "engine/window.hpp"


class VulkanContext
{
public:
    void init(const rc::Window& window);
    void cleanup();

    const VkInstance& getInstance() const;
    const VkSurfaceKHR& getSurface() const;

private:
    VkInstance instance = VK_NULL_HANDLE;
    VkSurfaceKHR surface = VK_NULL_HANDLE;

    void createInstance();
    void createSurface(const rc::Window& window);

    std::vector<const char*> getRequiredExtentions();
};