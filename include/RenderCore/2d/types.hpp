#pragma once

#include "../math/vector2D.hpp"

// All basics geometry shapes here

namespace rc
{   
    struct Rectangle
    {
        Vec2 position;
        Vec2 size;
    };

    struct Triangle
    {
        Vec2 A;
        Vec2 B;
        Vec2 C;

        static Triangle FromPoints(const Vec2& a, const Vec2& b, const Vec2& c);
        static Triangle Equilateral(const Vec2& center, float size);
        static Triangle Isosceles(const Vec2& center, float width, float height);
    };

    struct Circle
    {
        Vec2 position;
        float radius;
    };

    struct Line
    {
        Vec2 start;
        Vec2 end;
    };
}