#pragma once

#include <cstdint>

namespace rc
{
    struct Color
    {
        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t a = 255;
    };
}