#pragma once

#include "vector2D.hpp"
#include "vector3D.hpp"
#include "vector4.hpp"
#include "matrix4.hpp"
#include "quaternion.hpp"

namespace rc::Math
{
    constexpr float PI = 3.1415926535f;

    constexpr float DegToRad(float degrees)
    {
        return (degrees * PI / 180.f);
    }

    constexpr float RadToDeg(float radians)
    {
        return (radians * 180.f / PI);
    }
} 
