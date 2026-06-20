#define STB_IMAGE_IMPLEMENTATION
#include <lib/stb_image.h>
#include <stdexcept>

#include "engine/texture.hpp"
#include "vulkanBackend/vulkanBuffer.hpp"
#include "vulkanBackend/vulkanDevice.hpp"
#include "vulkanBackend/render/vulkanCommandBuffer.hpp"
#include "vulkanBackend/utils.hpp"

// helper functions will declarete here
VkCommandBuffer beginSingleTimeCommands(const VulkanDevice& vDevice, const VulkanCommandBuffer& cmd) 
{
    VkCommandBufferAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandPool = cmd.getCommandPool();
    allocInfo.commandBufferCount = 1;

    VkCommandBuffer commandBuffer;
    vkAllocateCommandBuffers(vDevice.getDevice(), &allocInfo, &commandBuffer);

    VkCommandBufferBeginInfo beginInfo{};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

    vkBeginCommandBuffer(commandBuffer, &beginInfo);

    return commandBuffer;
}

void endSingleTimeCommands(VkCommandBuffer commandBuffer, const VulkanDevice& vDevice, const VulkanCommandBuffer& cmd) 
{
    vkEndCommandBuffer(commandBuffer);

    VkSubmitInfo submitInfo{};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &commandBuffer;

    vkQueueSubmit(vDevice.getGraphicsQueue(), 1, &submitInfo, VK_NULL_HANDLE);
    vkQueueWaitIdle(vDevice.getGraphicsQueue());

    vkFreeCommandBuffers(vDevice.getDevice(), cmd.getCommandPool(), 1, &commandBuffer);
}

namespace rc
{
    void Texture2D::create(const VulkanDevice& vDevice, const VulkanCommandBuffer& cmd, const std::string& path)
    {
        int texWidth, texHeight, texChannels;

        stbi_set_flip_vertically_on_load(true);

        stbi_uc* pixels = stbi_load(path.c_str(), &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
        VkDeviceSize imageSize = texWidth * texHeight * 4;

        if (!pixels)
            throw std::runtime_error("Cannot load texture: " + path);

        mipLevels = static_cast<uint32_t>(std::floor(std::log2(std::max(texWidth, texHeight)))) + 1;

        VulkanBuffer stagingBuffer;
        stagingBuffer.create(vDevice, imageSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, pixels);

        stbi_image_free(pixels);

        createImage(vDevice, texWidth, texHeight, 
            VK_FORMAT_R8G8B8A8_SRGB, 
            VK_IMAGE_TILING_OPTIMAL, 
            VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT | VK_IMAGE_USAGE_SAMPLED_BIT,
            VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

        transitionImageLayout(vDevice, cmd, image,
            VK_FORMAT_R8G8B8A8_SRGB, 
            VK_IMAGE_LAYOUT_UNDEFINED, 
            VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, mipLevels);

        copyBufferToImage(vDevice, cmd, stagingBuffer.buffer, image, static_cast<uint32_t>(texWidth), static_cast<uint32_t>(texHeight));

        generateMipmaps(vDevice, cmd, image, VK_FORMAT_R8G8B8A8_SRGB, texWidth, texHeight, mipLevels);

        stagingBuffer.cleanup(vDevice.getDevice());

        createTextureImageView(vDevice.getDevice(), VK_FORMAT_R8G8B8A8_SRGB, mipLevels);
        createSampler(vDevice);
    }

    void Texture2D::cleanup(const VulkanDevice& vDevice)
    {
        vkDestroySampler(vDevice.getDevice(), sampler, nullptr);
        vkDestroyImageView(vDevice.getDevice(), imageView, nullptr);
        
        vkDestroyImage(vDevice.getDevice(), image, nullptr);
        vkFreeMemory(vDevice.getDevice(), imageMemory, nullptr);
    }

    void Texture2D::createImage(const VulkanDevice& vDevice, uint32_t width, uint32_t height, 
            VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, 
            VkMemoryPropertyFlags properties)
    {
        VkImageCreateInfo imageInfo{};
        imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
        imageInfo.imageType = VK_IMAGE_TYPE_2D;
        imageInfo.extent.width = width;
        imageInfo.extent.height = height;
        imageInfo.extent.depth = 1;
        imageInfo.format = format;
        imageInfo.mipLevels = mipLevels;
        imageInfo.tiling = tiling;
        imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        imageInfo.usage = usage;
        imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
        imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

        if (vkCreateImage(vDevice.getDevice(), &imageInfo, nullptr, &image) != VK_SUCCESS)
            throw std::runtime_error("Cannot create image for texture!");

        VkMemoryRequirements memRequirements;
        vkGetImageMemoryRequirements(vDevice.getDevice(), image, &memRequirements);

        VkMemoryAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        allocInfo.allocationSize = memRequirements.size;
        allocInfo.memoryTypeIndex = vkUtils::findMemoryType(vDevice.getPhysicalDevice(), memRequirements.memoryTypeBits, properties);

        if (vkAllocateMemory(vDevice.getDevice(), &allocInfo, nullptr, &imageMemory) != VK_SUCCESS)
            throw std::runtime_error("Cannot allocate memory for image!");

        vkBindImageMemory(vDevice.getDevice(), image, imageMemory, 0);
    }

    void Texture2D::createTextureImageView(VkDevice device, VkFormat format, uint32_t mipLevels)
    {   
        imageView = vkUtils::createImageView(device, image, 
            VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_ASPECT_COLOR_BIT, mipLevels);
    }
    
    void Texture2D::createSampler(const VulkanDevice& vDevice)
    {
        VkSamplerCreateInfo samplerInfo{};
        samplerInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
        samplerInfo.magFilter = VK_FILTER_NEAREST;
        samplerInfo.minFilter = VK_FILTER_NEAREST;

        samplerInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
        samplerInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
        samplerInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;
        
        samplerInfo.anisotropyEnable = VK_FALSE;

        VkPhysicalDeviceProperties properties{};
        vkGetPhysicalDeviceProperties(vDevice.getPhysicalDevice(), &properties);

        samplerInfo.maxAnisotropy = properties.limits.maxSamplerAnisotropy;
        samplerInfo.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
        samplerInfo.unnormalizedCoordinates = VK_FALSE;

        samplerInfo.compareEnable = VK_FALSE;
        samplerInfo.compareOp = VK_COMPARE_OP_ALWAYS;

        samplerInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
        samplerInfo.mipLodBias = 0.0f;
        samplerInfo.minLod = 0.0f;
        samplerInfo.maxLod = static_cast<float>(mipLevels);

        if (vkCreateSampler(vDevice.getDevice(), &samplerInfo, nullptr, &sampler) != VK_SUCCESS)
            throw std::runtime_error("Cannot create sampler for texture 2d!");
    }

    void Texture2D::transitionImageLayout(const VulkanDevice& vDevice, 
            const VulkanCommandBuffer& cmd,
            VkImage image, VkFormat format, 
            VkImageLayout oldLayout, VkImageLayout newLayout,
            uint32_t mipLevels)
    {
        VkCommandBuffer commandBuffer = beginSingleTimeCommands(vDevice, cmd);

        VkImageMemoryBarrier barrier{};
        barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
        barrier.oldLayout = oldLayout;
        barrier.newLayout = newLayout;

        barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;

        barrier.image = image;
        barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        barrier.subresourceRange.baseMipLevel = 0;
        barrier.subresourceRange.levelCount = mipLevels;
        barrier.subresourceRange.baseArrayLayer = 0;
        barrier.subresourceRange.layerCount = 1;

        VkPipelineStageFlags sourceStage;
        VkPipelineStageFlags destinationStage;

        if (oldLayout == VK_IMAGE_LAYOUT_UNDEFINED && newLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL) 
        {
            barrier.srcAccessMask = 0;
            barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;

            sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT; 
            destinationStage = VK_PIPELINE_STAGE_TRANSFER_BIT; 
        }
        else if (oldLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL && newLayout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL) 
        {
            barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
            barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

            sourceStage = VK_PIPELINE_STAGE_TRANSFER_BIT; 
            destinationStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
        }
        else 
        {
            throw std::invalid_argument("unsupported layout transition!");
        }

        vkCmdPipelineBarrier(
            commandBuffer,
            sourceStage, destinationStage,
            0,
            0, nullptr,
            0, nullptr,
            1, &barrier
        );

        endSingleTimeCommands(commandBuffer, vDevice, cmd);
    }

    void Texture2D::copyBufferToImage(const VulkanDevice& vDevice, const VulkanCommandBuffer& cmd, VkBuffer buffer, VkImage image, uint32_t width, uint32_t height)
    {
        VkCommandBuffer commandBuffer = beginSingleTimeCommands(vDevice, cmd);

        VkBufferImageCopy region{};
        region.bufferOffset = 0;
        region.bufferRowLength = 0;
        region.bufferImageHeight = 0;

        region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        region.imageSubresource.mipLevel = 0;
        region.imageSubresource.baseArrayLayer = 0;
        region.imageSubresource.layerCount = 1;

        region.imageOffset = {0, 0, 0};
        region.imageExtent = {
            width,
            height,
            1
        };

        vkCmdCopyBufferToImage(
            commandBuffer,
            buffer,
            image,
            VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
            1,
            &region
        );


        endSingleTimeCommands(commandBuffer, vDevice, cmd);
    }
    
    void Texture2D::generateMipmaps(const VulkanDevice& vDevice, const VulkanCommandBuffer& cmd, VkImage image,  VkFormat imageFormat,
            int32_t texWidth, int32_t texHeight, uint32_t mipLevels)
    {
        VkFormatProperties formatProperties;
        vkGetPhysicalDeviceFormatProperties(vDevice.getPhysicalDevice(), imageFormat, &formatProperties);

        if (!(formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT)) 
        {
            throw std::runtime_error("texture image format does not support linear blitting!");
        }


        VkCommandBuffer commandBuffer = beginSingleTimeCommands(vDevice, cmd);

        VkImageMemoryBarrier barrier{};
        barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
        barrier.image = image;
        barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        barrier.subresourceRange.baseArrayLayer = 0;
        barrier.subresourceRange.layerCount = 1;
        barrier.subresourceRange.levelCount = 1;

        int32_t mipWidth = texWidth;
        int32_t mipHeight = texHeight;

        for (uint32_t i = 1; i < mipLevels; ++i) 
        {
            barrier.subresourceRange.baseMipLevel = i - 1;
            barrier.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
            barrier.newLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
            barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
            barrier.dstAccessMask = VK_ACCESS_TRANSFER_READ_BIT;

            vkCmdPipelineBarrier(commandBuffer,
                VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT, 0,
                0, nullptr,
                0, nullptr,
                1, &barrier);

            VkImageBlit blit{};
            blit.srcOffsets[0] = { 0, 0, 0 };
            blit.srcOffsets[1] = { mipWidth, mipHeight, 1 };
            blit.srcSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
            blit.srcSubresource.mipLevel = i - 1;
            blit.srcSubresource.baseArrayLayer = 0;
            blit.srcSubresource.layerCount = 1;
            blit.dstOffsets[0] = { 0, 0, 0 };
            blit.dstOffsets[1] = { mipWidth > 1 ? mipWidth / 2 : 1, mipHeight > 1 ? mipHeight / 2 : 1, 1 };
            blit.dstSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
            blit.dstSubresource.mipLevel = i;
            blit.dstSubresource.baseArrayLayer = 0;
            blit.dstSubresource.layerCount = 1;

            vkCmdBlitImage(commandBuffer,
                image, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
                image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
                1, &blit,
                VK_FILTER_LINEAR); 
            
            barrier.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
            barrier.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
            barrier.srcAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
            barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

            vkCmdPipelineBarrier(commandBuffer,
                VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT, 0,
                0, nullptr,
                0, nullptr,
                1, &barrier);

            if (mipWidth > 1) mipWidth /= 2;
            if (mipHeight > 1) mipHeight /= 2;
        }

        barrier.subresourceRange.baseMipLevel = mipLevels - 1;
        barrier.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
        barrier.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
        barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
        barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

        vkCmdPipelineBarrier(commandBuffer,
            VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT, 0,
            0, nullptr,
            0, nullptr,
            1, &barrier);

        endSingleTimeCommands(commandBuffer, vDevice, cmd);
    }
}