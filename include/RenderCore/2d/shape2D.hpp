#pragma once

#include "types.hpp"
#include "RenderCore/core/rcRenderItem.hpp"

namespace rc
{
    class Material;
}

namespace rc::Shape2D
{
    RenderItem CreateRectangle(float x, float y, float w, float h, Material* material);
    RenderItem CreateRectangle(const Vec2& position, float w, float h, Material* material);
    RenderItem CreateRectangle(const Vec2& position, const Vec2& size, Material* material);
    RenderItem CreateRectangle(const Rectangle& rect, Material* material);

    // A, B and C - points
    RenderItem CreateTriangle(const Vec2& A, const Vec2& B, const Vec2& C, Material* material);
    RenderItem CreateTriangle(const Triangle& triangle, Material* material);
}