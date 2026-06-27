#pragma once

#include "RenderCore/math/matrix4.hpp"

struct UniformBufferObject
{
    alignas(16) rc::Mat4 view;
    alignas(16) rc::Mat4 proj;
};
