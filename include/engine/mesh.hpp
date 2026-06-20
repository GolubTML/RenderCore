#pragma once

#include <vector>
#include "vulkanBackend/vulkanBuffer.hpp"
#include "engine/vertex.hpp"

class VulkanCommandBuffer;

class Mesh
{
public:
    Mesh();
    ~Mesh();

    void create(const VulkanDevice& vDevice, 
        const std::vector<Vertex>& verticies, const std::vector<uint32_t>& indices);
    
    void cleanup(VkDevice device);

    void draw(const VulkanCommandBuffer& cmd, uint32_t currentFrame);

private:
    VulkanBuffer vertexBuffer;
    VulkanBuffer indexBuffer;

    uint32_t indexCount;
};