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

        static Color White() { return Color{ 255, 255, 255 }; }
        static Color Black() { return Color{ 0, 0, 0 }; }
        static Color Red() { return Color{ 255, 0, 0 }; }
        static Color DarkRed() { return Color{ 125, 0, 0 }; }
        static Color Green() { return Color{ 0, 255, 0 }; }
        static Color DarkGreen() { return Color{ 0, 125, 0 }; }
        static Color Blue() { return Color{ 0, 0, 255 }; }
        static Color DarkBlue() { return Color{ 0, 0, 125 }; }
        static Color Aque() { return Color{ 0, 255, 255 }; }
        static Color LightAque() { return Color{ 207, 248, 248 }; }
        static Color DarkAque() { return Color{ 36, 157, 159 }; }
        static Color Yellow() { return Color{ 255, 120, 0 }; }
        static Color LightYellow() { return Color{ 255, 180, 60 }; }
        static Color Orange() { return Color{ 255, 80, 0 }; }
        static Color Pink() { return Color{ 255, 0, 120 }; }
        static Color LightPink() { return Color{ 255, 60, 180 }; }
        static Color Purple() { return Color{ 147, 112, 219 }; }
    };
}