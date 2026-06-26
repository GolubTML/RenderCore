#pragma once

#include <vector>
#include <memory>
#include <vulkan/vulkan.hpp>

namespace rc
{
    class Texture2D;
    struct Material;
}

class MaterialSystem;

class ResourceManager
{
public:
    void init(MaterialSystem& matSys);

    template<typename T, typename... Args>
    T* create(Args&&... args);

    template<typename T>
    void destroy(T* resource);

    void cleanup(VkDevice device);

private:
    MaterialSystem* materialSystem = nullptr;

    std::vector<std::unique_ptr<rc::Texture2D>> textures;
    std::vector<std::unique_ptr<rc::Material>> materials;
};

#include "resourceManager.inl"