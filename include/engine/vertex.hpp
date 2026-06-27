#pragma once

#include <vulkan/vulkan.h>
#include "RenderCore/math/vector2D.hpp"
#include "RenderCore/math/vector3D.hpp"
#include "RenderCore/math/vector4.hpp"

#include <array>

struct Vertex
{
    rc::Vec3 pos;
    rc::Vec4 color;
    rc::Vec2 uvPos;

    static VkVertexInputBindingDescription getBindingDescription();
    static std::array<VkVertexInputAttributeDescription, 3> getAttributeDescription();

    // static uint32_t packColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);
    // static uint32_t applyColorFactor(uint32_t color, int factor);
};