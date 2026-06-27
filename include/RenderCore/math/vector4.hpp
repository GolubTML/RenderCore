#pragma once

#include "vector3D.hpp"

namespace rc
{
    struct Vec4
    {
        float x;
        float y;
        float z;
        float w;

        Vec4() = default;
        constexpr Vec4(float value) : x(value), y(value), z(value), w(value) { } 
        constexpr Vec4(float x, float y, float z, float w) 
            : x(x), y(y), z(z), w(w) { }
        Vec4(const Vec3& vec3, float w) : x(vec3.x), y(vec3.y), z(vec3.z), w(w) { }

        Vec4 operator+(const Vec4& other) const;
        Vec4 operator-(const Vec4& other) const;
        Vec4 operator*(float scalar) const;
        Vec4 operator/(float scalar) const;

        bool operator==(const Vec4& other) const;
        bool operator!=(const Vec4& other) const;

        float& operator[](int index);
        const float& operator[](int index) const;

        float dot(const Vec4& other) const;

        float length() const;
        float lengthSquared() const;

        void Normalize();
        Vec4 Normalized() const;

        Vec3 xyz() const;
        Vec3 Homogeneous() const;

        static Vec4 Point(const Vec3& p);
        static Vec4 Direction(const Vec3& p);

        static Vec4 Zero();
        static Vec4 One();
    };
}