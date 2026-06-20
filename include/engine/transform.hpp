#pragma once

#include <glm/glm.hpp>

namespace rc
{
    struct Transform
    {
        glm::vec3 position{0.f};
        glm::vec3 rotation{0.f};
        glm::vec3 scale{1.f};
    
        glm::mat4 getModelMatrix() const;
    };
}