#pragma once

#include "engine/window.hpp"
#include "engine/camera.hpp"
#include "engine/mesh.hpp"

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

    void DrawMesh(Mesh& mesh);
    void DestroyMesh(Mesh& mesh);

    Mesh CreateRectangle(float w, float h, const Color& color);
}