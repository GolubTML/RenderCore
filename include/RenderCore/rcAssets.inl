#pragma once

#include "rcAssets.hpp"
#include "rcInternal.hpp"
#include "engine/resourceManager.hpp"

#include <utility>

namespace rc::Assets
{
    template<typename T, typename... Args>
    static T* Create(Args&&... args)
    {
        return Internal::gResourceManager->create<T>(std::forward<Args>(args)...);
    }
    
    template<typename T>
    static void Destroy(T* resource)
    {
        Internal::gResourceManager->destroy(resource);
    }
}