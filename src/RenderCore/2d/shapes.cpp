#include "RenderCore/2d/shape2D.hpp"
#include <vector>
#include <utility>
#include "RenderCore/rcInternal.hpp"
#include "vulkanBackend/vulkanDevice.hpp"
#include "engine/mesh.hpp"
#include "RenderCore/core/rcMaterial.hpp"
#include "RenderCore/math/math.hpp"
#include "RenderCore/rcAssets.hpp"

#include <cmath>
#include <memory>

namespace rc::Shape2D
{
    std::pair<std::vector<Vertex>, std::vector<uint32_t>> CreateRectangleData(float w, float h, const Color& color);
    std::pair<std::vector<Vertex>, std::vector<uint32_t>> CreateTriangleData(const Triangle& triangle, const Color& color);
    std::pair<std::vector<Vertex>, std::vector<uint32_t>> CreateCircleData(const Circle& circle, const Color& color);

    RenderItem CreateRectangle(float x, float y, float w, float h, Material* material)
    {
        if (!material) throw std::runtime_error("Material is nullptr!");

        Rectangle rect {.position = Vec2(x, y), .size = Vec2(w, h)};

        return CreateRectangle(rect, material);
    }

    RenderItem CreateRectangle(const Vec2& position, float w, float h, Material* material)
    {
        if (!material) throw std::runtime_error("Material is nullptr!");

        Rectangle rect {.position = position, .size = Vec2(w, h)};

        return CreateRectangle(rect, material);
    }

    RenderItem CreateRectangle(const Vec2& position, const Vec2& size, Material* material)
    {
        if (!material) throw std::runtime_error("Material is nullptr!");

        Rectangle rect {.position = position, .size = size};

        return CreateRectangle(rect, material);
    }

    RenderItem CreateRectangle(const Rectangle& rect, Material* material)
    {
        if (!material) throw std::runtime_error("Material is nullptr!");

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

    RenderItem CreateRectangle(float x, float y, float w, float h, Color color)
    {
        Rectangle rect {.position = Vec2(x, y), .size = Vec2(w, h)};

        return CreateRectangle(rect, Assets::Create<Material>(color));
    }

    RenderItem CreateRectangle(const Vec2& position, float w, float h, Color color)
    {
        Rectangle rect {.position = position, .size = Vec2(w, h)};

        return CreateRectangle(rect, Assets::Create<Material>(color));
    }

    RenderItem CreateRectangle(const Vec2& position, const Vec2& size, Color color)
    {
        Rectangle rect {.position = position, .size = size};

        return CreateRectangle(rect, Assets::Create<Material>(color));
    }

    RenderItem CreateRectangle(const Rectangle& rect, Color color)
    {
        return CreateRectangle(rect, Assets::Create<Material>(color));
    }


    RenderItem CreateTriangle(const Vec2& A, const Vec2& B, const Vec2& C, Material* material)
    {
        if (!material) throw std::runtime_error("Material is nullptr!");

        Triangle triangle = { A, B, C };

        return CreateTriangle(triangle, material);
    }

    RenderItem CreateTriangle(const Triangle& triangle, Material* material)
    {
        if (!material) throw std::runtime_error("Material is nullptr!");

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

    RenderItem CreateTriangle(const Vec2& A, const Vec2& B, const Vec2& C, Color color)
    {
        Triangle triangle = { A, B, C };

        return CreateTriangle(triangle, Assets::Create<Material>(color));
    }

    RenderItem CreateTriangle(const Triangle& triangle, Color color)
    {
        return CreateTriangle(triangle, Assets::Create<Material>(color));
    }


    RenderItem CreateCircle(const Vec2& pos, float radius, Material* material)
    {
        if (!material) throw std::runtime_error("Material is nullptr!");

        // by default, there will be 32 segments
        Circle circle
        {
            .position = pos,
            .radius = radius,
            .segments = 32
        };

        return CreateCircle(circle, material);
    }

    RenderItem CreateCircle(const Circle& circle, Material* material)
    {
        if (!material) throw std::runtime_error("Material is nullptr!");

        auto data = CreateCircleData(circle, material->color);

        RenderItem item 
        {
            .mesh = new Mesh(),
            .transform = 
            {
                rc::Vec3(circle.position, 0.f), 
                rc::Quaternion::Identity(), 
                rc::Vec3::One()
            },
            .material = material
        };

        item.mesh->create(*Internal::gVulkDevice, data.first, data.second);

        return item;
    }

    RenderItem CreateCircle(const Vec2& pos, float radius, Color color)
    {
        Circle circle
        {
            .position = pos,
            .radius = radius,
            .segments = 32
        };

        return CreateCircle(circle, Assets::Create<Material>(color));
    }

    RenderItem CreateCircle(const Circle& circle, Color color)
    {
        return CreateCircle(circle, Assets::Create<Material>(color));
    }

    RenderItem CreateLine(const Vec2& start, const Vec2& end, float thickness, Material* material)
    {
        if (!material) throw std::runtime_error("Material is nullptr!");

        Line line {.start = start, .end = end};

        return CreateLine(line, thickness, material);
    }

    RenderItem CreateLine(const Line& line, float thickness, Material* material)
    {
        if (!material) throw std::runtime_error("Material is nullptr!");
        
        Vec2 delta = line.end - line.start;
        float length = delta.length();

        Vec2 center = (line.start + line.end) * 0.5f;

        auto item = CreateRectangle(center, length, thickness, material);

        float angle = Math::RadToDeg(atan2(delta.y, delta.x));

        item.transform.rotation = Quaternion::FromAxisAngle(Vec3::Forward(), angle);

        return item;
    }

    RenderItem CreateLine(const Vec2& start, const Vec2& end, float thickness, Color color)
    {
        return CreateLine({start, end}, thickness, Assets::Create<Material>(color));
    }
    
    RenderItem CreateLine(const Line& line, float thickness, Color color)
    {
        return CreateLine(line, thickness, Assets::Create<Material>(color));
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

    std::pair<std::vector<Vertex>, std::vector<uint32_t>> CreateCircleData(const Circle& circle, const Color& color)
    {
        float r = static_cast<float>(color.r) / 255.f;
        float g = static_cast<float>(color.g) / 255.f;
        float b = static_cast<float>(color.b) / 255.f;
        float a = static_cast<float>(color.a) / 255.f;

        std::vector<Vertex> vertices;
        std::vector<uint32_t> indices;

        vertices.reserve(circle.segments + 1);
        indices.reserve(circle.segments * 3);

        vertices.emplace_back(Vertex{ {0.f, 0.f, 0.f}, {r, g, b, a}, {0.5f, 0.5f} });

        float step =  2.f * Math::PI / static_cast<float>(circle.segments);

        for (uint16_t i = 0; i < circle.segments; ++i)
        {
            float angle = static_cast<float>(i) * step;

            float x = circle.radius * cos(angle);
            float y = circle.radius * sin(angle);

            float u = x / (2.f * circle.radius) + 0.5f;
            float v = y / (2.f * circle.radius) + 0.5f;

            vertices.emplace_back(Vertex{ {x, y, 0}, {r, g, b, a}, {u, v} });
        }

        for (uint16_t i = 1; i <= circle.segments; ++i)
        {
            indices.push_back(0); 
            indices.push_back(i);

            if (i == circle.segments)
                indices.push_back(1);
            else
                indices.push_back(i + 1);
        }

        return std::make_pair(vertices, indices);
    }
}