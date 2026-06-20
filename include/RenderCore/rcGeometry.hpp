#pragma once

#include "engine/mesh.hpp"
#include "RenderCore/rcTypes.hpp"

#include <utility>
#include <vector>

namespace rc::Geometry
{
    std::pair<std::vector<Vertex>, std::vector<uint32_t>> CreateRectangleData(float w, float h, const Color& color);
}