#include "engine/resourceManager.hpp"

#include "RenderCore/core/rcTexture2D.hpp"
#include "RenderCore/core/rcMaterial.hpp"

#include "engine/materialSystem.hpp"

void ResourceManager::init(MaterialSystem& matSys)
{
    materialSystem = &matSys;
}

void ResourceManager::cleanup(VkDevice device)
{  
    for (auto& mat : materials)
        materialSystem->destroyMaterial(*mat);

    materials.clear();
    textures.clear();
}