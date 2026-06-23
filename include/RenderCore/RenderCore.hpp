#pragma once

#include "engine/window.hpp"
#include "engine/camera/camera2D.hpp"
#include "engine/camera/camera3D.hpp"
#include "engine/renderItem.hpp"
#include "engine/shader.hpp"
#include "engine/materials/material.hpp"
#include "engine/materials/texture.hpp"

#include "RenderCore/rcTypes.hpp"
#include "RenderCore/rcTime.hpp"
#include "RenderCore/rcInput.hpp"

namespace rc
{
    void Init();
    void InitVulkan(Window& window);

    void SetCamera(rc::Camera& camera);
    void SetShaders(Shader vertex, Shader fragment);

    void Terminate();

    void ClearColor(float r, float g, float b);
    void BeginFrame();
    void EndFrame();

    void DrawObject(RenderItem& item);

    RenderItem CreateRectangle(const glm::vec2& position, float w, float h, Material* material);
    void DestroyObject(RenderItem& item);

    Shader LoadShader(const std::string& path, ShaderType type);

    // overloads for this function
    // if has texture, we will use it
    Material* CreateMaterial(Color color, Texture2D& texture); 
    // if there is no texture, we will use 1 by 1 white texture
    Material* CreateMaterial(Color color);         
                
    void DestroyMaterial(Material* material);
    
    Texture2D LoadTexture(const std::string& path);
}