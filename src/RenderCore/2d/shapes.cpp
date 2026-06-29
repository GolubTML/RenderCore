#include "RenderCore/2d/shape2D.hpp"
#include <vector>
#include <utility>
#include "RenderCore/rcInternal.hpp"
#include "vulkanBackend/vulkanDevice.hpp"
#include "engine/mesh.hpp"
#include "RenderCore/core/rcMaterial.hpp"

namespace rc::Shape2D
{
    std::pair<std::vector<Vertex>, std::vector<uint32_t>> CreateRectangleData(float w, float h, const Color& color);
    std::pair<std::vector<Vertex>, std::vector<uint32_t>> CreateTriangleData(const Triangle& triangle, const Color& color);

    RenderItem CreateRectangle(float x, float y, float w, float h, Material* material)
    {
        Rectangle rect {.position = Vec2(x, y), .size = Vec2(w, h)};

        return CreateRectangle(rect, material);
    }

    RenderItem CreateRectangle(const Vec2& position, float w, float h, Material* material)
    {
        Rectangle rect {.position = position, .size = Vec2(w, h)};

        return CreateRectangle(rect, material);
    }

    RenderItem CreateRectangle(const Vec2& position, const Vec2& size, Material* material)
    {
        Rectangle rect {.position = position, .size = size};

        return CreateRectangle(rect, material);
    }

    RenderItem CreateRectangle(const Rectangle& rect, Material* material)
    {
        auto data = CreateRectangleData(rect.size.x, rect.size.y, material->color);

        RenderItem item 
        {
            .mesh = new Mesh(),
            .transform = 
            {
                rc::Vec3(rect.position, 0.f), 
                rc::Quaternion::Identity(), 
                rc::Vec3::One()
            },
            .material = material
        };

        item.mesh->create(*Internal::gVulkDevice, data.first, data.second);

        return item;
    }

    RenderItem CreateTriangle(const Vec2& A, const Vec2& B, const Vec2& C, Material* material)
    {
        Triangle triangle = { A, B, C };

        return CreateTriangle(triangle, material);
    }

    RenderItem CreateTriangle(const Triangle& triangle, Material* material)
    {
        auto data = CreateTriangleData(triangle, material->color);

        Vec2 center = Vec2((triangle.A.x + triangle.B.x + triangle.C.x) / 3.f,
                           (triangle.A.y + triangle.B.y + triangle.C.y) / 3.f);

        RenderItem item 
        {
            .mesh = new Mesh(),
            .transform = 
            { 
                rc::Vec3(center, 0.f), 
                rc::Quaternion::Identity(), 
                rc::Vec3::One()
            },
            .material = material
        };

        item.mesh->create(*Internal::gVulkDevice, data.first, data.second);

        return item;
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

    std::pair<std::vector<Vertex>, std::vector<uint32_t>> CreateTriangleData(const Triangle& triangle, const Color& color)
    {

        float r = static_cast<float>(color.r) / 255.f;
        float g = static_cast<float>(color.g) / 255.f;
        float b = static_cast<float>(color.b) / 255.f;
        float a = static_cast<float>(color.a) / 255.f;

        Vec2 center = Vec2((triangle.A.x + triangle.B.x + triangle.C.x) / 3.f,
                           (triangle.A.y + triangle.B.y + triangle.C.y) / 3.f);

        std::vector<Vertex> vertices =
        {
            {
                {triangle.A.x - center.x, triangle.A.y - center.y, 0},
                {r,g,b,a},
                {0.f,0.f}
            },

            {
                {triangle.B.x - center.x, triangle.B.y - center.y, 0},
                {r,g,b,a},
                {1.f,0.f}
            },

            {
                {triangle.C.x - center.x, triangle.C.y - center.y, 0},
                {r,g,b,a},
                {0.5f,1.f}
            }
        };

        std::vector<uint32_t> indices =
        {
            0,1,2,
        };

        return std::make_pair(vertices, indices);
    }
}