#pragma once

#include "engine/camera/camera.hpp"

namespace rc
{
    class Camera3D : public Camera
    {
    public:
        Camera3D(const glm::vec3& pos, float fov, float w, float h);

        glm::mat4 getView() const override;
        glm::mat4 getProjection() const override;

        glm::vec3 position{0.f};

    private:
        float width;
        float height;

        glm::vec3 front{0.f};
        glm::vec3 up{0.f};

        float fov;
    };
}