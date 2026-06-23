#pragma once

#include <RenderCore/rcTypes.hpp>
#include <vulkan/vulkan.hpp>

class MaterialSystem;
class VulkanRenderer;

namespace rc
{
    class Texture2D;

    class Material
    {
    public:
        Color color = {255, 255, 255, 255};
        Texture2D* texture = nullptr;

    private:
        VkDescriptorSet descriptorSet = VK_NULL_HANDLE;

        friend class ::MaterialSystem;
        friend class ::VulkanRenderer;
    };
}