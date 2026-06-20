#include "RenderCore/rcGeometry.hpp"

namespace rc::Geometry
{
    std::pair<std::vector<Vertex>, std::vector<uint32_t>> CreateRectangleData(float w, float h, const Color& color)
    {
        float r = static_cast<float>(color.r / 255);
        float g = static_cast<float>(color.g / 255);
        float b = static_cast<float>(color.b / 255);

        std::vector<Vertex> vertices =
        {
            { {-w / 2, -h / 2, 0}, {r, g, b} },
            { { w / 2, -h / 2, 0}, {r, g, b} },
            { { w / 2,  h / 2, 0}, {r, g, b} },
            { {-w / 2,  h / 2, 0}, {r, g, b} }
        };

        std::vector<uint32_t> indices =
        {
            0,1,2,
            2,3,0
        };

        return std::make_pair(vertices, indices);
    }
}