#include "RenderCore/core/rcShader.hpp"
#include "RenderCore/rcInternal.hpp"
#include "vulkanBackend/vulkanShader.hpp"
#include "vulkanBackend/vulkanDevice.hpp"

#include <filesystem>

namespace rc
{
    Shader::Shader(const std::string& path, ShaderType type)
    {
        handle = std::make_unique<VulkanShader>();

        std::filesystem::path exeDir = std::filesystem::canonical("/proc/self/exe").parent_path();
        std::filesystem::path fullPath = exeDir / path;

        switch (type)
        {
            case ShaderType::VERTEX:
                handle->load(fullPath.string(), Internal::gVulkDevice->getDevice(), VK_SHADER_STAGE_VERTEX_BIT);
                break;

            case ShaderType::FRAGMENT:
                handle->load(fullPath.string(), Internal::gVulkDevice->getDevice(), VK_SHADER_STAGE_FRAGMENT_BIT);
                break;

            default:
                throw std::invalid_argument("Unsupported shader type!");
        }
    }

    Shader::~Shader()
    {
        Destroy();
    }

    void Shader::Destroy()
    {
        if (!handle)
            return;

        handle->cleanup(Internal::gVulkDevice->getDevice());
        handle.reset();
    }
}