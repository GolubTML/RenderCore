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

    // overloads for this function
    // if has texture, we will use it
    Material* CreateMaterial(Color color, Texture2D& texture); 
    // if there is no texture, we will use 1 by 1 white texture
    Material* CreateMaterial(Color color);         
                
    void DestroyMaterial(Material* material);
}