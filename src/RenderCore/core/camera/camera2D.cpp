#include "RenderCore/core/camera/camera2D.hpp"
#include <glm/gtc/matrix_transform.hpp>

namespace rc
{
    Camera2D::Camera2D(float width, float height)   
        : width(width), height(height) 
    {
        position = {0.f, 0.f};
    }

    glm::mat4 Camera2D::getView() const 
    {
        return glm::translate(glm::mat4(1.f), glm::vec3(-position.x, -position.y, 0));
    }

    glm::mat4 Camera2D::getProjection() const
    {
        return glm::ortho(0.f, width, 0.f, height, -1.f, 1.f);
    }

    void Camera2D::onResize(int width, int height) 
    {
        this->width = width;
        this->height = height;
    }
}