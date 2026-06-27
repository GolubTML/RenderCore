#include "RenderCore/math/vector4.hpp"
#include <cmath>
#include <cassert>

namespace rc
{
    Vec4 Vec4::operator+(const Vec4& other) const
    {
        return Vec4(this->x + other.x,
                    this->y + other.y,
                    this->z + other.z,
                    this->w + other.w);
    }
    Vec4 Vec4::operator-(const Vec4& other) const
    {
        return Vec4(this->x - other.x,
                    this->y - other.y,
                    this->z - other.z,
                    this->w - other.w);
    }
    Vec4 Vec4::operator*(float scalar) const
    {
        return Vec4(this->x * scalar,
                    this->y * scalar,
                    this->z * scalar,
                    this->w * scalar);
    }
    Vec4 Vec4::operator/(float scalar) const
    {
        assert(scalar != 0);

        return Vec4(this->x / scalar,
                    this->y / scalar,
                    this->z / scalar,
                    this->w / scalar);
    }

    bool Vec4::operator==(const Vec4& other) const
    {
        constexpr float epsilon = 0.00001f;

        return abs(x - other.x) < epsilon && abs(y - other.y) < epsilon && abs(z - other.z) < epsilon && abs(w - other.w) < epsilon;
    }
    bool Vec4::operator!=(const Vec4& other) const
    {
        return !(*this == other);
    }

    float& Vec4::operator[](int index)
    {
        return (&x)[index];
    }
    const float& Vec4::operator[](int index) const
    {
        return (&x)[index];
    }

    float Vec4::dot(const Vec4& other) const
    {
        return ((this->x * other.x) + (this->y * other.y) + (this->z * other.z) + (this->w * other.w));
    }

    float Vec4::length() const
    {
        return sqrt(x * x + y * y + z * z + w * w);
    }
    float Vec4::lengthSquared() const
    {
        return (x * x + y * y + z * z + w * w);
    }

    void Vec4::Normalize()
    {
        float len = length();

        if (len != 0)
        {
            x /= len;
            y /= len;
            z /= len;
            w /= len;
        }
    }
    Vec4 Vec4::Normalized() const
    {
        float len = length();

        if (len != 0)
        {
            return Vec4(
                x / len,
                y / len,
                z / len,
                w / len
            );
        }
        else
            return Vec4(0.f);
    }

    Vec3 Vec4::xyz() const
    {
        return Vec3(x, y, z);
    }

    Vec3 Vec4::Homogeneous() const
    {
        if (std::abs(w) < 0.00001f)
            return Vec3(x, y, z);

        return Vec3(x / w, y / w, z / w);
    }

    Vec4 Vec4::Point(const Vec3& p)
    {
        return Vec4(p, 1.f);
    }
    Vec4 Vec4::Direction(const Vec3& p)
    {
        return Vec4(p, 0.f);
    }

    Vec4 Vec4::Zero()
    {
        return Vec4(0.f);
    }
    Vec4 Vec4::One()
    {
        return Vec4(1.f);
    }
}