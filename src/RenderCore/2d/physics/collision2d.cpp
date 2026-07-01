#include "RenderCore/2d/physics/collision2D.hpp"
#include "RenderCore/2d/types.hpp"

#include <algorithm>

namespace rc::Collision2D
{
    bool Intersects(const Rectangle& rect1, const Rectangle& rect2)
    {
        Vec2 halfA = rect1.size * 0.5f;
        Vec2 halfB = rect2.size * 0.5f;

        return
            std::abs(rect1.position.x - rect2.position.x) <= halfA.x + halfB.x &&
            std::abs(rect1.position.y - rect2.position.y) <= halfA.y + halfB.y;
    }
}