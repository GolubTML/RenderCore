#pragma once

#include "engine/camera/camera.hpp"

namespace rc
{
    class Camera2D : public Camera
    {
    public:
        Camera2D(float width, float height);

        glm::mat4 getView() const override;
        glm::mat4 getProjection() const override;

        glm::vec2 position;

    private:
        float width;
        float height;
    };
}