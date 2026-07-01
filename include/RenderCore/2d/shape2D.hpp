#pragma once

#include "types.hpp"
#include "RenderCore/core/rcRenderItem.hpp"

namespace rc
{
    class Material;
}

namespace rc::Shape2D
{
    // Rectangles
    RenderItem CreateRectangle(float x, float y, float w, float h, Material* material);
    RenderItem CreateRectangle(const Vec2& position, float w, float h, Material* material);
    RenderItem CreateRectangle(const Vec2& position, const Vec2& size, Material* material);
    RenderItem CreateRectangle(const Rectangle& rect, Material* material);

    RenderItem CreateRectangle(float x, float y, float w, float h, Color color);
    RenderItem CreateRectangle(const Vec2& position, float w, float h, Color color);
    RenderItem CreateRectangle(const Vec2& position, const Vec2& size, Color color);
    RenderItem CreateRectangle(const Rectangle& rect, Color color);

    // Triangles
    // A, B and C - points
    RenderItem CreateTriangle(const Vec2& A, const Vec2& B, const Vec2& C, Material* material);
    RenderItem CreateTriangle(const Triangle& triangle, Material* material);

    RenderItem CreateTriangle(const Vec2& A, const Vec2& B, const Vec2& C, Color color);
    RenderItem CreateTriangle(const Triangle& triangle, Color color);

    // Circles
    RenderItem CreateCircle(const Vec2& pos, float radius, Material* material);
    RenderItem CreateCircle(const Circle& circle, Material* material);

    RenderItem CreateCircle(const Vec2& pos, float radius, Color color);
    RenderItem CreateCircle(const Circle& circle, Color color);

    // Line
    RenderItem CreateLine(const Vec2& start, const Vec2& end, float thickness, Material* material);
    RenderItem CreateLine(const Line& line, float thickness, Material* material);
    RenderItem CreateLine(const Vec2& start, const Vec2& end, float thickness, Color color);
    RenderItem CreateLine(const Line& line, float thickness, Color color);
}