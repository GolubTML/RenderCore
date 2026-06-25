#include "RenderCore/rcTexture2D.hpp"
#include "RenderCore/rcInternal.hpp"

#include "vulkanBackend/vulkanTexture.hpp"
#include "vulkanBackend/vulkanDevice.hpp"

#include <filesystem>
#include <iostream>

namespace rc
{
    Texture2D::Texture2D()
    {
        handle = std::make_unique<VulkanTexture>();
    }

    Texture2D::Texture2D(const std::string& path)
    {
        handle = std::make_unique<VulkanTexture>();

        std::filesystem::path exeDir = std::filesystem::canonical("/proc/self/exe").parent_path();
        std::filesystem::path fullPath = exeDir / path;

        handle->create(*Internal::gVulkDevice, *Internal::gCmd, fullPath);
    }

    Texture2D::~Texture2D()
    {
        std::cout << "Deleted texture: " << this << "\n";

        if (handle)
            handle->cleanup(Internal::gVulkDevice->getDevice());
    }
}