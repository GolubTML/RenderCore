#include "RenderCore/core/camera/camera3D.hpp"
#include <glm/gtc/matrix_transform.hpp>

namespace rc
{
    Camera3D::Camera3D(const glm::vec3& pos, float fov, float w, float h)
        : position(pos), fov(fov), width(w), height(h) 
    {
        front = glm::vec3(0.f, 0.f, -1.f);
        up = glm::vec3(0.f, 1.f, 0.f);
    }

    glm::mat4 Camera3D::getView() const
    {
        return glm::lookAt(position, front + position, up);
    }

    glm::mat4 Camera3D::getProjection() const
    {
        glm::mat4 projection = glm::perspective(glm::radians(fov), width / height, 0.1f, 100.f);
        projection[1][1] *= -1;

        return projection;
    }

    void Camera3D::onResize(int width, int height)
    {
        this->width = width;
        this->height = height;
    }
}