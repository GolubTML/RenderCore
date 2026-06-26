#pragma once

#include "engine/resourceManager.hpp"

#include "RenderCore/core/rcTexture2D.hpp"
#include "RenderCore/core/rcMaterial.hpp"
#include "RenderCore/core/rcShader.hpp"
#include "RenderCore/rcInternal.hpp"

#include "engine/materialSystem.hpp"
#include "engine/mesh.hpp"

#include "vulkanBackend/vulkanDevice.hpp"

template<typename T, typename... Args>
T* ResourceManager::create(Args&&... args)
{
    if constexpr (std::is_same_v<T, rc::Texture2D>)
    {
        auto resource = std::make_unique<rc::Texture2D>(std::forward<Args>(args)...);

        T* ptr = resource.get();

        textures.push_back(std::move(resource));

        return ptr;
    }
    else if constexpr (std::is_same_v<T, rc::Material>)
    {
        auto resource = std::make_unique<rc::Material>();

        materialSystem->createMaterial(*resource, std::forward<Args>(args)...);
                
        T* ptr = resource.get();
        
        materials.push_back(std::move(resource));

        return ptr;
    }
    else if constexpr (std::is_same_v<T, rc::Shader>)
    {
        auto resource = std::make_unique<rc::Shader>(std::forward<Args>(args)...);

        T* ptr = resource.get();

        shaders.push_back(std::move(resource));

        return ptr;
    }
}

template<typename T>
void ResourceManager::destroy(T* resource)
{
    if constexpr (std::is_same_v<T, rc::Texture2D>)
    {
        auto it = std::find_if(
            textures.begin(), textures.end(),
            [&](auto& ptr)
            {
                return ptr.get() == resource;
            }
        );

        if (it != textures.end())
            textures.erase(it);
    }
    else if constexpr (std::is_same_v<T, rc::Material>)
    {
        auto it = std::find_if(
            materials.begin(), materials.end(),
            [&](auto& ptr)
            {
                return ptr.get() == resource;
            }
        );

        if (it != materials.end())
        {
            materialSystem->destroyMaterial(it->get());
            materials.erase(it);
        }
    }
    else if constexpr (std::is_same_v<T, rc::Shader>)
    {
        auto it = std::find_if(
            shaders.begin(), shaders.end(),
            [&](auto& ptr)
            {
                return ptr.get() == resource;
            }
        );

        if (it != shaders.end())
            shaders.erase(it);
    }
}