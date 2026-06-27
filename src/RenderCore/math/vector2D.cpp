#include "RenderCore/math/vector2D.hpp"
#include "RenderCore/math/math.hpp"
#include <cmath>
#include <algorithm>
#include <cassert>

namespace rc
{
    Vec2 Vec2::operator+(const Vec2& other) const
    {
        return Vec2(x + other.x, y + other.y);
    }
    Vec2 Vec2::operator-(const Vec2& other) const
    {
        return Vec2(x - other.x, y - other.y);
    }

    Vec2 Vec2::operator-() const
    {
        return Vec2(-x, -y);
    }

    Vec2 Vec2::operator*(float scalar) const
    {
        return Vec2(x * scalar, y * scalar);
    }
    Vec2 Vec2::operator/(float scalar) const
    {
        assert(scalar != 0);

        return Vec2(x / scalar, y / scalar);
    }

    Vec2& Vec2::operator+=(const Vec2& other)
    {
        x += other.x;
        y += other.y; 

        return *this;
    }
    Vec2& Vec2::operator-=(const Vec2& other)
    {
        x -= other.x;
        y -= other.y; 

        return *this;
    }
    Vec2& Vec2::operator*=(float scalar)
    {   
        x *= scalar;
        y *= scalar; 

        return *this;
    }
    Vec2& Vec2::operator/=(float scalar)
    {
        if (scalar == 0)
            return *this;

        x /= scalar;
        y /= scalar; 

        return *this;
    }

    Vec2& Vec2::operator=(const Vec2& other)
    {
        this->x = other.x;
        this->y = other.y;

        return *this;
    }

    bool Vec2::operator==(const Vec2& other) const
    {
        constexpr float epsilon = 0.00001f;

        return std::abs(x - other.x) < epsilon && std::abs(y - other.y) < epsilon;
    }

    bool Vec2::operator!=(const Vec2& other) const
    {
        return !(*this == other);
    }

    float Vec2::length() const
    {
        return sqrt(x * x + y * y);
    }
    float Vec2::lengthSquared() const
    {
        return (x * x + y * y);
    }

    float Vec2::dot(const Vec2& other) const
    {
        return ((this->x * other.x) + (this->y * other.y));
    }

    float Vec2::cross(const Vec2& other) const
    {
        return ((this->x * other.y) - (this->y * other.x));
    }

    float Vec2::distance(const Vec2& other) const
    {
        float dx = other.x - this->x;
        float dy = other.y - this->y;

        return sqrt(dx * dx + dy * dy);
    }
    float Vec2::distanceSquared(const Vec2& other) const
    {
        float dx = other.x - this->x;
        float dy = other.y - this->y;

        return (dx * dx + dy * dy);
    }

    float Vec2::angleRad() const
    {
        // this will return angle of vector
        return atan2(y, x);
    }

    float Vec2::minComponent() const
    {
        return std::min(x, y);
    }

    float Vec2::maxComponent() const
    {
        return std::max(x, y);
    }

    Vec2 Vec2::Abs() const
    {
        return Vec2(std::abs(x), std::abs(y));
    }

    Vec2 Vec2::rotateDeg(float deg) const
    {
        float oldX = x;
        float oldY = y;

        float radians = Math::DegToRad(deg);

        float cosAngle = cos(radians);
        float sinAngle = sin(radians);

        // should we use radiants instead?
        return Vec2(oldX * cosAngle - oldY * sinAngle,
                    oldX * sinAngle + oldY * cosAngle);
    }

    Vec2 Vec2::rotateRad(float rad) const
    {
        float oldX = x;
        float oldY = y;

        float cosAngle = cos(rad);
        float sinAngle = sin(rad);

        // should we use radiants instead?
        return Vec2(oldX * cosAngle - oldY * sinAngle,
                    oldX * sinAngle + oldY * cosAngle);
    }

    void Vec2::Normalize()
    {
        float len = length();

        if (len != 0)
        {
            x /= len;
            y /= len;
        }
    }

    Vec2 Vec2::Normalized()
    {
        float len = length();

        if (len != 0)
            return Vec2(x / len, y / len);
        else
            return Vec2(0, 0);
    }

    Vec2 Vec2::Perpendicular()
    {
        // this is the easiest one

        return Vec2(-y, x); // or -vec.y, vec.x?
    }

    Vec2 Vec2::Lerp(const Vec2& a, const Vec2& b, float t)
    {
        float clampedT = std::clamp(t, 0.f, 1.f);

        return Vec2(a + (b - a) * clampedT);
    }

    Vec2 Vec2::UnclampedLerp(const Vec2& a, const Vec2& b, float t)
    {
        return Vec2(a + (b - a) * t);
    }

    Vec2 Vec2::Min(const Vec2& a, const Vec2& b)
    {
        return Vec2(std::min(a.x, b.x), std::min(a.y, b.y));
    }
    Vec2 Vec2::Max(const Vec2& a, const Vec2& b)
    {
        return Vec2(std::max(a.x, b.x), std::max(a.y, b.y));
    }

    Vec2 Vec2::Clamp(const Vec2& min, const Vec2& max) const
    {
        return Vec2(std::clamp(x, min.x, max.x),
                    std::clamp(y, min.y, max.y));
    }

    constexpr Vec2 Vec2::Zero() { return Vec2(0, 0); }
    constexpr Vec2 Vec2::One() { return Vec2(1, 1); }
    constexpr Vec2 Vec2::Up() { return Vec2(0, 1); }
    constexpr Vec2 Vec2::Down() { return Vec2(0, -1); }
    constexpr Vec2 Vec2::Left() { return Vec2(-1, 0); }
    constexpr Vec2 Vec2::Right() { return Vec2(1, 0); }
}