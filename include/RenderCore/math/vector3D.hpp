#pragma once

#include "vector2D.hpp"

namespace rc
{
    struct Vec3
    {
        float x;
        float y;
        float z;
        
        Vec3() = default;
        constexpr Vec3(float value) : x(value), y(value), z(value) { }
        constexpr Vec3(float x, float y, float z) : x(x), y(y), z(z) { }
        Vec3(const Vec2& vec2, float z) : x(vec2.x), y(vec2.y), z(z) { }
        
        Vec3 operator+(const Vec3& other) const;
        Vec3 operator-(const Vec3& other) const;
        Vec3 operator-() const;

        Vec3 operator*(float scalar) const;
        Vec3 operator/(float scalar) const;

        Vec3& operator+=(const Vec3& other);
        Vec3& operator-=(const Vec3& other);
        Vec3& operator*=(float scalar);
        Vec3& operator/=(float scalar);

        Vec3& operator=(const Vec3& other);

        bool operator==(const Vec3& other) const;
        bool operator!=(const Vec3& other) const;

        float& operator[](int index);
        const float& operator[](int index) const;

        float length() const;
        float lengthSquared() const;

        float dot(const Vec3& other) const;

        float distance(const Vec3& other) const;
        float distanceSquared(const Vec3& other) const;

        float angleRad(const Vec3& other) const;

        Vec3 cross(const Vec3& other) const;

        void Normalize();
        Vec3 Normalized() const;

        Vec3 Reflect(const Vec3& normal) const;

        static Vec3 Lerp(const Vec3& a, const Vec3& b, float t);
        static Vec3 UnclampedLerp(const Vec3& a, const Vec3& b, float t);
        static Vec3 Min(const Vec3& a, const Vec3& b);
        static Vec3 Max(const Vec3& a, const Vec3& b);
        Vec3 Clamp(const Vec3& min, const Vec3& max) const;

        Vec2 xy() const;
        Vec2 xz() const;
        Vec2 yz() const;

        static Vec3 Zero();
        static Vec3 One();

        static Vec3 Up();
        static Vec3 Down();
        static Vec3 Left();
        static Vec3 Right();
        static Vec3 Forward();
        static Vec3 Back();
    }; 
}