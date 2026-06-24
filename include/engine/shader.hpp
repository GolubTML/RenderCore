#pragma once

#include <string>
#include <vector>
#include <vulkan/vulkan.h>

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
        Shader(const std::string& path, VkDevice device, VkShaderStageFlagBits shaderFlag);

        void load(const std::string& path, VkDevice device, VkShaderStageFlagBits shaderFlag);
        void cleanup(VkDevice device);

        VkPipelineShaderStageCreateInfo getStageInfo() const;

    private:
        VkShaderModule module;
        VkPipelineShaderStageCreateInfo shaderStage{};

        std::vector<char> readFile(const std::string& path);
    };

    // Now, loading method for engine classes will here
    Shader LoadShader(const std::string& path, ShaderType type);
}