#include "engine/mesh.hpp"
#include "vulkanBackend/render/vulkanCommandBuffer.hpp"
#include "vulkanBackend/vulkanDevice.hpp"

namespace rc
{
    Mesh::~Mesh() { }

    void Mesh::create(const VulkanDevice& vDevice, 
        const std::vector<Vertex>& verticies, const std::vector<uint32_t>& indices)
    {
        if (vertexBuffer.buffer != VK_NULL_HANDLE)
            vertexBuffer.cleanup(vDevice.getDevice());
    
        if (indexBuffer.buffer != VK_NULL_HANDLE)
            indexBuffer.cleanup(vDevice.getDevice());
    
        VkDeviceSize vertexBufSize = sizeof(Vertex) * verticies.size();
        vertexBuffer.create(vDevice, vertexBufSize, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, verticies.data());
    
        VkDeviceSize indexBufSize = sizeof(uint32_t) * indices.size();
        indexBuffer.create(vDevice, indexBufSize, VK_BUFFER_USAGE_INDEX_BUFFER_BIT, indices.data());
    
        indexCount = indices.size();
    }
    
    void Mesh::cleanup(VkDevice device)
    {
        vertexBuffer.cleanup(device);
        indexBuffer.cleanup(device);
    }
    
    void Mesh::draw(const VulkanCommandBuffer& cmd, uint32_t currentFrame)
    {
        VkBuffer buffers[] = { vertexBuffer.buffer };
        VkDeviceSize offsets[] = { 0 };
    
        vkCmdBindVertexBuffers(cmd.getCommandBuffers()[currentFrame], 0, 1, buffers, offsets);
        vkCmdBindIndexBuffer(cmd.getCommandBuffers()[currentFrame], indexBuffer.buffer, 0, VK_INDEX_TYPE_UINT32);
    
        vkCmdDrawIndexed(cmd.getCommandBuffers()[currentFrame], indexCount, 1, 0, 0, 0);
    }
}