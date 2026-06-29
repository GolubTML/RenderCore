#pragma once

#include <cstdint>
#include <string>
#include "RenderCore/math/vector3D.hpp"
#include "RenderCore/math/matrix4.hpp"
#include "RenderCore/math/quaternion.hpp"

namespace rc
{
    struct Transform
    {
        Vec3 position{0.f};
        Quaternion rotation = Quaternion::Identity();
        Vec3 scale{1.f};
    
        Mat4 getModelMatrix() const;
    };

    struct WindowDesc
    {
        int width;
        int height;
        std::string title;

        bool resizable = false;
    };

    struct Color
    {
        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t a = 255;
    };
}