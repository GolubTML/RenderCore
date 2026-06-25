#include "vulkanBackend/vulkanContext.hpp"
#include "RenderCore/core/rcWindow.hpp"
#include <stdexcept>

const std::vector<const char*> validationLayers = {
    "VK_LAYER_KHRONOS_validation"
};

void VulkanContext::init(const rc::Window& window)
{
    createInstance();
    createSurface(window);
}

void VulkanContext::cleanup()
{
    if (surface != VK_NULL_HANDLE)
        vkDestroySurfaceKHR(instance, surface, nullptr);
    
    if (instance != VK_NULL_HANDLE)
        vkDestroyInstance(instance, nullptr);
}

const VkInstance& VulkanContext::getInstance() const
{
    return instance;
}

const VkSurfaceKHR& VulkanContext::getSurface() const
{
    return surface;
}

void VulkanContext::createInstance()
{
    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "None";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_3;

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    auto extensions = getRequiredExtentions();
    createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size()); 
    createInfo.ppEnabledExtensionNames = extensions.data();

    // there should be DebugMessenger

    // FOR TEST
    createInfo.enabledLayerCount = validationLayers.size();
    createInfo.ppEnabledLayerNames = validationLayers.data();
    createInfo.pNext = nullptr;

    if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS)
        throw std::runtime_error("Cannot create vulkan instance!");
}

void VulkanContext::createSurface(const rc::Window& window)
{
    if (glfwCreateWindowSurface(instance, window.getWindowHandle(), nullptr, &surface) != VK_SUCCESS)
        throw std::runtime_error("Cannot create window surface!");
}

std::vector<const char*> VulkanContext::getRequiredExtentions()
{
    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;

    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

    // if (Debug::enableValidationLayers)
    // {
    //     extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    // }

    return extensions;
}