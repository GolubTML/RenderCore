#pragma once

#include <glm/glm.hpp>

namespace rc
{
    class Camera
    {
    public:
        Camera() = default;
        Camera(glm::vec3 position, float fov, float w, float h);
        ~Camera();

        glm::mat4 getCameraView() const;
        glm::mat4 getCameraProjection() const;

    private:
        glm::vec3 pos = glm::vec3(0.f);
        glm::vec3 front = glm::vec3(0.f);
        glm::vec3 up = glm::vec3(0.f);

        float FOV = 0.f;
        float width;
        float height;
    };
}