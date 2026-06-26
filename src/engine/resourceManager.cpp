#include "engine/resourceManager.hpp"

#include "RenderCore/core/rcTexture2D.hpp"
#include "RenderCore/core/rcMaterial.hpp"
#include "RenderCore/core/rcShader.hpp"

#include "engine/materialSystem.hpp"

void ResourceManager::init(MaterialSystem& matSys)
{
    materialSystem = &matSys;
}

void ResourceManager::cleanup(VkDevice device)
{  
    for (auto& mat : materials)
        materialSystem->destroyMaterial(*mat);

    for (auto& shader : shaders)
        shader->Destroy();

    shaders.clear();
    materials.clear();
    textures.clear();
}