#pragma once

#include "RenderCore/core/rcWindow.hpp"
#include "RenderCore/core/rcRenderItem.hpp"
#include "RenderCore/core/rcShader.hpp"
#include "RenderCore/core/camera/camera2D.hpp"
#include "RenderCore/core/camera/camera3D.hpp"
#include "RenderCore/core/rcMaterial.hpp"
#include "RenderCore/core/rcTexture2D.hpp"

#include "RenderCore/rcAssets.hpp"
#include "RenderCore/rcTypes.hpp"
#include "RenderCore/rcTime.hpp"
#include "RenderCore/rcInput.hpp"
#include "RenderCore/rcShapes.hpp"

namespace rc
{
    void Init();
    void InitVulkan(Window& window);

    void SetCamera(rc::Camera& camera);
    void SetShaders(const Shader& vertex, const Shader& fragment);

    void Terminate();

    void ClearColor(float r, float g, float b);
    void BeginFrame();
    void EndFrame();

    void DrawObject(RenderItem& item);
}