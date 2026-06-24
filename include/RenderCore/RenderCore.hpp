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
#include "RenderCore/rcShapes.hpp"

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
}