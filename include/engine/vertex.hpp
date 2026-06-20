#pragma once

#include <glm/glm.hpp>
#include <vulkan/vulkan.h>

struct Vertex
{
    glm::vec3 pos;
    glm::vec3 color;
    // glm::vec2 uvPos;

    static VkVertexInputBindingDescription getBindingDescription();
    static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescription();

    // static uint32_t packColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);
    // static uint32_t applyColorFactor(uint32_t color, int factor);
};