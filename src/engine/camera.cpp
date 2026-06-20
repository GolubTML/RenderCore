#include "engine/camera.hpp"
#include <glm/gtc/matrix_transform.hpp>

namespace rc
{
    Camera::Camera(glm::vec3 position, float fov, float w, float h) : pos(position), FOV(fov), width(w), height(h)
    {
        front = glm::vec3(0.f, 0.f, -1.f);
        up = glm::vec3(0.f, 1.f, 0.f);
    }

    Camera::~Camera() { }

    glm::mat4 Camera::getCameraView() const
    {
        return glm::lookAt(pos, front + pos, up);
    }

    glm::mat4 Camera::getCameraProjection() const
    {
        return glm::perspective(glm::radians(FOV), width / height, 0.1f, 100.f);
    }
}