#pragma once

#include "RenderCore/math/matrix4.hpp"

namespace rc
{
    class Camera
    {
    public:
        virtual ~Camera() = default;

        virtual rc::Mat4 getView() const = 0;
        virtual rc::Mat4 getProjection() const = 0;

        virtual void onResize(int width, int height) = 0;
    };
}