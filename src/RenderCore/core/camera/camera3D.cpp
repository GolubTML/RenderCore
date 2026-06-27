#include "RenderCore/core/camera/camera3D.hpp"

namespace rc
{
    Camera3D::Camera3D(const rc::Vec3& pos, float fov, float w, float h)
        : position(pos), fov(fov), width(w), height(h) 
    {
        front = rc::Vec3::Forward();
        up = rc::Vec3::Up();
    }

    rc::Mat4 Camera3D::getView() const
    {
        return rc::Mat4::LookAt(position, front + position, up);
    }

    rc::Mat4 Camera3D::getProjection() const
    {
        rc::Mat4 projection = rc::Mat4::Perspective(fov, width / height, 0.1f, 100.f);
        projection[1][1] *= -1;

        return projection;
    }

    void Camera3D::onResize(int width, int height)
    {
        this->width = width;
        this->height = height;
    }
}