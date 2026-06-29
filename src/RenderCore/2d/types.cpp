#include "RenderCore/2d/types.hpp"
#include <cmath>

namespace rc
{
    Triangle Triangle::FromPoints(const Vec2& a, const Vec2& b, const Vec2& c)
    {
        return {a, b, c};
    }
    Triangle Triangle::Equilateral(const Vec2& center, float size)
    {
        float height = size * sqrt(3.f) / 2.f;

        return
        {
            Vec2(center.x, center.y - height / 2),
            Vec2(center.x - size / 2, center.y + height / 2),
            Vec2(center.x + size / 2, center.y + height / 2)
        };
    }
    Triangle Triangle::Isosceles(const Vec2& center, float width, float height)
    {
        return
        {
            Vec2(center.x, center.y - height / 2),
            Vec2(center.x - width / 2, center.y + height / 2),
            Vec2(center.x + width / 2, center.y + height / 2)
        };
    }
}