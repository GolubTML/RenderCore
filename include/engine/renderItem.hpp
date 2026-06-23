#pragma once

#include "engine/mesh.hpp"
#include "engine/transform.hpp"
#include "engine/materials/material.hpp"

namespace rc
{
    struct RenderItem
    {
        Mesh mesh;
        Transform transform;

        Material* material = nullptr;
    };
}