#pragma once

#include "RenderCore/core/camera/camera.hpp"
#include "RenderCore/math/vector2D.hpp"

namespace rc
{
    class Camera2D : public Camera
    {
    public:
        Camera2D(float width, float height);

        rc::Mat4 getView() const override;
        rc::Mat4 getProjection() const override;

        void onResize(int width, int height) override;

        rc::Vec2 position;

    private:
        float width;
        float height;
    };
}