#pragma once

#include <string>
#include <memory>

class VulkanTexture;
class MaterialSystem;

namespace rc
{
    class Texture2D
    {
    public:
        Texture2D();
        Texture2D(const std::string& path);
        
        ~Texture2D();

    private:
        std::unique_ptr<VulkanTexture> handle;

        friend class ::MaterialSystem;
    };
}