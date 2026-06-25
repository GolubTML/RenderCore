#pragma once

#include "RenderCore/rcTypes.hpp"

namespace rc
{
    class Mesh;
    struct Material;

    struct RenderItem
    {
        Mesh* mesh;
        rc::Transform transform;

        Material* material = nullptr;
    };
}