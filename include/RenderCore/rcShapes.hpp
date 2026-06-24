#pragma once

#include "engine/renderItem.hpp"
#include "RenderCore/rcTypes.hpp"

#include <vector>

namespace rc
{
    class Material;
}

namespace rc::Shapes
{
    RenderItem CreateRectangle(const glm::vec2& position, float w, float h, Material* material);
    
    void DestroyObject(RenderItem& item);
}