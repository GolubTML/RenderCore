#include "RenderCore/core/camera/camera2D.hpp"
#include "RenderCore/math/vector3D.hpp"

namespace rc
{
    Camera2D::Camera2D(float width, float height)   
        : width(width), height(height) 
    {
        position = rc::Vec2(0.f, 0.f);
    }

    rc::Mat4 Camera2D::getView() const 
    {
        return rc::Mat4::Translate(rc::Mat4(1.f), rc::Vec3(-position.x, -position.y, 0));
    }

    rc::Mat4 Camera2D::getProjection() const
    {
        return rc::Mat4::Orthographic(0.f, width, 0.f, height, -1.f, 1.f);
    }

    void Camera2D::onResize(int width, int height) 
    {
        this->width = width;
        this->height = height;
    }
}