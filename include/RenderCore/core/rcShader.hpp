#pragma once

#include <string>
#include <memory>

class VulkanShader;
class VulkanPipeline;

namespace rc
{
    enum class ShaderType
    {
        VERTEX,
        FRAGMENT
    };

    class Shader
    {
    public:
        Shader(const std::string& path, ShaderType type);
        ~Shader();

        void Destroy();

    private:
        std::unique_ptr<VulkanShader> handle;

        friend class ::VulkanPipeline;
    };
}