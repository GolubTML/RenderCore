#pragma once

#include <glm/glm.hpp>

namespace rc
{
    class Camera
    {
    public:
        // Camera() = default;
        // Camera(glm::vec3 position, float fov, float w, float h);
        virtual ~Camera() = default;

        virtual glm::mat4 getView() const = 0;
        virtual glm::mat4 getProjection() const = 0;
    };
}