#include "RenderCore/math/vector3D.hpp"
#include <cassert>
#include <cmath>
#include <algorithm>

namespace rc
{
    Vec3 Vec3::operator+(const Vec3& other) const
    {
        return Vec3(this->x + other.x, this->y + other.y, this->z + other.z);
    }
    Vec3 Vec3::operator-(const Vec3& other) const
    {
        return Vec3(this->x - other.x, this->y - other.y, this->z - other.z);
    }

    Vec3 Vec3::operator-() const
    {
        return Vec3(-x, -y, -z);
    }

    Vec3 Vec3::operator*(float scalar) const
    {
        return Vec3(this->x * scalar, this->y * scalar, this->z * scalar);
    }
    Vec3 Vec3::operator/(float scalar) const
    {
        assert(scalar != 0);

        return Vec3(this->x / scalar, this->y / scalar, this->z / scalar);
    }

    Vec3& Vec3::operator+=(const Vec3& other)
    {
        x += other.x;
        y += other.y;
        z += other.z;

        return *this;
    }
    Vec3& Vec3::operator-=(const Vec3& other)
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;

        return *this;
    }
    Vec3& Vec3::operator*=(float scalar)
    {
        x *= scalar;
        y *= scalar;
        z *= scalar;

        return *this;
    }
    Vec3& Vec3::operator/=(float scalar)
    {
        assert(scalar != 0);

        x /= scalar;
        y /= scalar;
        z /= scalar;

        return *this;
    }

    bool Vec3::operator==(const Vec3& other) const
    {
        constexpr float epsilon = 0.00001f;

        return abs(x - other.x) < epsilon && abs(y - other.y) < epsilon && abs(z - other.z) < epsilon;
    }
    bool Vec3::operator!=(const Vec3& other) const
    {
        return !(*this == other);
    }

    float& Vec3::operator[](int index)
    {
        return (&x)[index];
    }
    const float& Vec3::operator[](int index) const
    {
        return (&x)[index];
    }

    float Vec3::length() const
    {
        return sqrt(x * x + y * y + z * z);
    }
    float Vec3::lengthSquared() const
    {
        return (x * x + y * y + z * z);
    }

    float Vec3::dot(const Vec3& other) const
    {
        return ((this->x * other.x) + (this->y * other.y) + (this->z * other.z));
    }

    float Vec3::distance(const Vec3& other) const
    {
        float dx = other.x - this->x;
        float dy = other.y - this->y;
        float dz = other.z - this->z;

        return sqrt(dx * dx + dy * dy + dz * dz);
    }
    float Vec3::distanceSquared(const Vec3& other) const
    {
        float dx = other.x - this->x;
        float dy = other.y - this->y;
        float dz = other.z - this->z;

        return (dx * dx + dy * dy + dz * dz);
    }

    float Vec3::angleRad(const Vec3& other) const
    {
        float value = dot(other) / (length() * other.length());

        value = std::clamp(value, -1.0f, 1.0f);

        return value;
    }

    Vec3 Vec3::cross(const Vec3& other) const
    {
        return Vec3(this->y * other.z - this->z * other.y,
                    this->z * other.x - this->x * other.z,
                    this->x * other.y - this->y * other.x);
    }

    void Vec3::Normalize()
    {
        float len = length();

        if (len != 0)
            *this /= len;
    }
    Vec3 Vec3::Normalized() const
    {
        float len = length();

        if (len != 0)
            return Vec3(x / len, y / len, z / len);
        else 
            return Vec3(0.f);
    }

    Vec3 Vec3::Reflect(const Vec3& normal) const
    {
        return *this - normal * (2.f * dot(normal));
    }


    Vec3 Vec3::Lerp(const Vec3& a, const Vec3& b, float t)
    {
        float clampedT = std::clamp(t, 0.f, 1.f);

        return Vec3(a + (b - a) * clampedT);
    }

    Vec3 Vec3::UnclampedLerp(const Vec3& a, const Vec3& b, float t)
    {
        return Vec3(a + (b - a) * t);
    }

    Vec3 Vec3::Min(const Vec3& a, const Vec3& b)
    {
        return Vec3(std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z));
    }
    Vec3 Vec3::Max(const Vec3& a, const Vec3& b)
    {
        return Vec3(std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z));
    }

    Vec3 Vec3::Clamp(const Vec3& min, const Vec3& max) const
    {
        return Vec3(std::clamp(this->x, min.x, max.x),
                    std::clamp(this->y, min.y, max.y),
                    std::clamp(this->z, min.z, max.z));
    }

    Vec2 Vec3::xy() const
    {
        return Vec2(this->x, this->y);
    }
    Vec2 Vec3::xz() const
    {
        return Vec2(this->x, this->z);
    }
    Vec2 Vec3::yz() const
    {
        return Vec2(this->y, this->z);
    }

    Vec3 Vec3::Zero()
    {
        return Vec3(0.f);
    }
    Vec3 Vec3::One()
    {
        return Vec3(1.f);
    }

    Vec3 Vec3::Up()
    {
        return Vec3(0, 1, 0);
    }
    Vec3 Vec3::Down()
    {
        return Vec3(0, -1, 0);
    }
    Vec3 Vec3::Left()
    {
        return Vec3(-1, 0, 0);
    }
    Vec3 Vec3::Right()
    {
        return Vec3(1, 0, 0);
    }
    Vec3 Vec3::Forward()
    {
        return Vec3(0, 0, -1);
    }
    Vec3 Vec3::Back()
    {   
        return Vec3(0, 0, 1);
    }
}