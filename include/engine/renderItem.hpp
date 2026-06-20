#pragma once

#include "engine/mesh.hpp"
#include "engine/transform.hpp"

namespace rc
{
    struct RenderItem
    {
        rc::Mesh mesh;
        rc::Transform transform;
    };
}