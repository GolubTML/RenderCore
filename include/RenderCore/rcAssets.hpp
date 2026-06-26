#pragma once

namespace rc::Assets
{
    template<typename T, typename... Args>
    static T* Create(Args&&... args);
    
    template<typename T>
    static void Destroy(T* resource);
}

#include "rcAssets.inl"