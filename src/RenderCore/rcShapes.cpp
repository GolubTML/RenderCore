#include "RenderCore/rcShapes.hpp"
#include "RenderCore/core/rcMaterial.hpp"

#include "RenderCore/rcInternal.hpp"
#include "vulkanBackend/vulkanDevice.hpp"
#include "engine/mesh.hpp"

#include "RenderCore/rcAssets.hpp"

#include <utility>

namespace rc::Shapes
{
    std::pair<std::vector<Vertex>, std::vector<uint32_t>> CreateRectangleData(float w, float h, const Color& color);

    RenderItem CreateRectangle(const rc::Vec2& position, float w, float h, Material* material)
    {
        auto data = CreateRectangleData(w, h, material->color);

        RenderItem item 
        {
            .mesh = new Mesh(),
            .transform = {rc::Vec3(position, 0.f), rc::Vec3::Zero(), rc::Vec3::One()},
            .material = material
        };

        item.mesh->create(*Internal::gVulkDevice, data.first, data.second);

        return item;
    }

    void DestroyObject(RenderItem& item)
    {
        item.mesh->cleanup(Internal::gVulkDevice->getDevice());
    }


    // helper function
    std::pair<std::vector<Vertex>, std::vector<uint32_t>> CreateRectangleData(float w, float h, const Color& color)
    {
        float r = static_cast<float>(color.r) / 255.f;
        float g = static_cast<float>(color.g) / 255.f;
        float b = static_cast<float>(color.b) / 255.f;
        float a = static_cast<float>(color.a) / 255.f;

        std::vector<Vertex> vertices =
        {
            { {-w / 2, -h / 2, 0}, {r, g, b, a}, {0.f, 0.f} },
            { { w / 2, -h / 2, 0}, {r, g, b, a}, {1.f, 0.f} },
            { { w / 2,  h / 2, 0}, {r, g, b, a}, {1.f, 1.f} },
            { {-w / 2,  h / 2, 0}, {r, g, b, a}, {0.f, 1.f} }
        };

        std::vector<uint32_t> indices =
        {
            0,1,2,
            2,3,0
        };

        return std::make_pair(vertices, indices);
    }
}