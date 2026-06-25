#pragma once

#include <cstdint>
#include <string>
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

    struct WindowDesc
    {
        int width;
        int height;
        std::string title;

        bool resizable = false;
    };

    struct Color
    {
        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t a = 255;
    };
}