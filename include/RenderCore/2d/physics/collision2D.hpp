#pragma once

namespace rc
{
    struct Rectangle;
}

namespace rc::Collision2D
{
    bool Intersects(const Rectangle& rect1, const Rectangle& rect2);
}