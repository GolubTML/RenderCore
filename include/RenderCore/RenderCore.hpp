#pragma once

#include "engine/window.hpp"
#include "engine/camera/camera2D.hpp"
#include "engine/camera/camera3D.hpp"
#include "engine/renderItem.hpp"

#include "RenderCore/rcTypes.hpp"

namespace rc
{
    void Init();
    void InitVulkan(Window& window);

    void SetCamera(rc::Camera& camera);

    void Terminate();

    void ClearColor(float r, float g, float b);
    void BeginFrame();
    void EndFrame();

    void DrawObject(RenderItem& item);
    void DestroyObject(RenderItem& item);

    RenderItem CreateRectangle(const glm::vec2& position, float w, float h, const Color& color);
}