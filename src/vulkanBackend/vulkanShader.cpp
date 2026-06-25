#include "vulkanBackend/vulkanShader.hpp"
#include <iostream>
#include <stdexcept>
#include <fstream>
#include <filesystem>

#include "vulkanBackend/vulkanDevice.hpp"
#include "RenderCore/rcInternal.hpp"

void VulkanShader::load(const std::string& path, VkDevice device, VkShaderStageFlagBits shaderFlag)
{
    auto shaderCode = readFile(path);

    VkShaderModuleCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo.codeSize = shaderCode.size();
    createInfo.pCode = reinterpret_cast<const uint32_t*>(shaderCode.data());

    if (vkCreateShaderModule(device, &createInfo, nullptr, &module) != VK_SUCCESS)
        throw std::runtime_error("Cannot create shader module!");

    shaderStage.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    shaderStage.stage = shaderFlag;
    shaderStage.module = module;
    shaderStage.pName = "main"; 
}

void VulkanShader::cleanup(VkDevice device)
{
    vkDestroyShaderModule(device, module, nullptr);
}

VkPipelineShaderStageCreateInfo VulkanShader::getStageInfo() const
{
    return shaderStage;
}

std::vector<char> VulkanShader::readFile(const std::string& path)
{
    std::ifstream file(path, std::ios::ate | std::ios::binary);

    if (!file.is_open()) 
        throw std::runtime_error("failed to open file");

    size_t fileSize = (size_t)file.tellg();
    std::vector<char> buffer(fileSize);

    file.seekg(0);
    file.read(buffer.data(), fileSize);

    file.close();

    return buffer;
}

    //Shader LoadShader(const std::string& path, ShaderType type)
    //{
    //    std::filesystem::path exeDir = std::filesystem::canonical("/proc/self/exe").parent_path();
    //    std::filesystem::path fullPath = exeDir / path;

    //    switch (type)
    //    {
    //        case ShaderType::VERTEX:
    //            return Shader(fullPath.string(), Internal::gVulkDevice->getDevice(), VK_SHADER_STAGE_VERTEX_BIT);

    //        case ShaderType::FRAGMENT:
    //            return Shader(fullPath.string(), Internal::gVulkDevice->getDevice(), VK_SHADER_STAGE_FRAGMENT_BIT);

    //        default:
    //            throw std::invalid_argument("Unsupported shader type!");
    //    }
    //}
