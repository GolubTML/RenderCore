#pragma once

#include <vector>
#include "vulkanBackend/vulkanBuffer.hpp"
#include "engine/vertex.hpp"

class VulkanCommandBuffer;

namespace rc
{
    class Mesh
    {
    public:
        Mesh() = default;
        ~Mesh();

        Mesh(const Mesh&) = delete;
        Mesh& operator=(const Mesh&) = delete;
        
        Mesh(Mesh&& other) noexcept;
        Mesh& operator=(Mesh&& other) noexcept;
    
        void create(const VulkanDevice& vDevice, 
            const std::vector<Vertex>& verticies, const std::vector<uint32_t>& indices);
        
        void cleanup(VkDevice device);
        
        void draw(const VulkanCommandBuffer& cmd, uint32_t currentFrame);
        
    private:
        VulkanBuffer vertexBuffer;
        VulkanBuffer indexBuffer;
        
        uint32_t indexCount;
    };
}