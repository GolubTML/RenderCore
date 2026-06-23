#pragma once

#include <vulkan/vulkan.hpp>
#include <string>

class VulkanDevice;
class VulkanCommandBuffer;

namespace rc
{
    class Texture2D
    {
    public:
        Texture2D() = default;
        ~Texture2D() = default;

        void create(const VulkanDevice& vDevice, const VulkanCommandBuffer& cmd, const std::string& path);
        void cleanup(VkDevice device);

        void createWhitePixel(const VulkanDevice& vDevice, const VulkanCommandBuffer& cmd);

        const VkImageView& getImageView() const;
        const VkSampler& getSampler() const;

    private:
        uint32_t mipLevels = 1;

        VkImage image = VK_NULL_HANDLE;
        VkDeviceMemory imageMemory = VK_NULL_HANDLE;
        VkImageView imageView = VK_NULL_HANDLE;
        VkSampler sampler = VK_NULL_HANDLE;

        void createImage(const VulkanDevice& vDevice, uint32_t width, uint32_t height, 
            VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, 
            VkMemoryPropertyFlags properties);
    
        void createTextureImageView(VkDevice device, VkFormat format, uint32_t mipLevels);
        void createSampler(const VulkanDevice& vDevice);

        void transitionImageLayout(const VulkanDevice& vDevice, 
            const VulkanCommandBuffer& cmd,
            VkImage image, VkFormat format, 
            VkImageLayout oldLayout, VkImageLayout newLayout,
            uint32_t mipLevels);

        void copyBufferToImage(const VulkanDevice& vDevice, const VulkanCommandBuffer& cmd, VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);

        void generateMipmaps(const VulkanDevice& vDevice, const VulkanCommandBuffer& cmd, VkImage image,  VkFormat imageFormat,
            int32_t texWidth, int32_t texHeight, uint32_t mipLevels);
    };
};