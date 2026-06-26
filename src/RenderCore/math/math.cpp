#include "RenderCore/math/math.hpp"

namespace rc::Math
{
    constexpr float DegToRad(float degrees)
    {
        return (degrees * PI / 180.f);
    }

    constexpr float RadToDeg(float radians)
    {
        return (radians * 180.f / PI);
    }
}