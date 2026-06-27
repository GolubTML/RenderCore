#pragma once

#include "RenderCore/core/camera/camera.hpp"
#include "RenderCore/math/vector3D.hpp"

namespace rc
{
    class Camera3D : public Camera
    {
    public:
        Camera3D(const rc::Vec3& pos, float fov, float w, float h);

        rc::Mat4 getView() const override;
        rc::Mat4 getProjection() const override;

        void onResize(int width, int height) override;

        rc::Vec3 position;

    private:
        float width;
        float height;

        rc::Vec3 front;
        rc::Vec3 up;

        float fov;
    };
}