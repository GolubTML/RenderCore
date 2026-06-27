#pragma once

namespace rc
{
    struct Vec2
    {
        float x;
        float y;

        Vec2() = default;
        constexpr Vec2(float x, float y) : x(x), y(y) { }

        Vec2 operator+(const Vec2& other) const;
        Vec2 operator-(const Vec2& other) const;
        Vec2 operator-() const;

        Vec2 operator*(float scalar) const;
        Vec2 operator/(float scalar) const;

        Vec2& operator+=(const Vec2& other);
        Vec2& operator-=(const Vec2& other);
        Vec2& operator*=(float scalar);
        Vec2& operator/=(float scalar);

        bool operator==(const Vec2& other) const;
        bool operator!=(const Vec2& other) const;

        float length() const;
        float lengthSquared() const; // without sqrt, for performance
        
        float dot(const Vec2& other) const;
        float cross(const Vec2& other) const;
        
        float distance(const Vec2& other) const;
        float distanceSquared(const Vec2& other) const; // also for performance
        
        float angleRad() const; 

        float minComponent() const;
        float maxComponent() const;

        Vec2 Abs() const;

        Vec2 rotateDeg(float deg) const;
        Vec2 rotateRad(float rad) const;

        void Normalize();
        Vec2 Normalized();
        Vec2 Perpendicular();

        static Vec2 Lerp(const Vec2& a, const Vec2& b, float t);
        static Vec2 UnclampedLerp(const Vec2& a, const Vec2& b, float t);
        static Vec2 Min(const Vec2& a, const Vec2& b);
        static Vec2 Max(const Vec2& a, const Vec2& b);
        Vec2 Clamp(const Vec2& min, const Vec2& max) const;

        constexpr static Vec2 Zero();
        constexpr static Vec2 One();
        constexpr static Vec2 Up();
        constexpr static Vec2 Down();
        constexpr static Vec2 Left();
        constexpr static Vec2 Right();
    };
}