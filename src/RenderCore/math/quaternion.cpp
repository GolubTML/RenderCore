#include "RenderCore/math/quaternion.hpp"
#include "RenderCore/math/math.hpp"
#include <cmath>

namespace rc
{
    Quaternion Quaternion::operator+(const Quaternion& other) const
    {
        return Quaternion(
            this->x + other.x,
            this->y + other.y,
            this->z + other.z,
            this->w + other.w
        );
    }
    Quaternion Quaternion::operator-(const Quaternion& other) const
    {
        return Quaternion(
            this->x - other.x,
            this->y - other.y,
            this->z - other.z,
            this->w - other.w
        );
    }

    Quaternion Quaternion::operator*(const Quaternion& other) const
    {
        return Quaternion(
            w * other.x + x * other.w + y * other.z - z * other.y,
            w * other.y - x * other.z + y * other.w + z * other.x,
            w * other.z + x * other.y - y * other.x + z * other.w,
            w * other.w - x * other.x - y * other.y - z * other.z
        );
    }
    Quaternion Quaternion::operator*(float scalar) const
    {
        return Quaternion(
            this->x * scalar,
            this->y * scalar,
            this->z * scalar,
            this->w * scalar
        );
    }

    Quaternion& Quaternion::operator+=(const Quaternion& other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
        w += other.w;

        return *this;
    }

    Quaternion& Quaternion::operator-=(const Quaternion& other)
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        w -= other.w;

        return *this;
    }

    Quaternion& Quaternion::operator*=(const Quaternion& other)
    {
        float newX = w * other.x + x * other.w + y * other.z - z * other.y;
        float newY = w * other.y - x * other.z + y * other.w + z * other.x;
        float newZ = w * other.z + x * other.y - y * other.x + z * other.w;
        float newW = w * other.w - x * other.x - y * other.y - z * other.z;

        x = newX;
        y = newY;
        z = newZ;
        w = newW;

        Normalize();

        return *this;
    }

    float Quaternion::length() const
    {
        return sqrt(x * x + y * y + z * z + w * w);
    }
    float Quaternion::lengthSquared() const
    {
        return (x * x + y * y + z * z + w * w);
    }

    void Quaternion::Normalize()
    {
        float len = length();

        if (len == 0)
        {
            x = y = z = 0;
            w = 1;

            return;
        }

        x /= len;
        y /= len;
        z /= len;
        w /= len;
    }
    Quaternion Quaternion::Normalized() const
    {
        Quaternion result;

        float len = length();

        if (len == 0)
        {
            return result; // should return Quaternion like this -> (0, 0, 0, 1)
        }

        result.x = x / len;
        result.y = y / len;
        result.z = z / len;
        result.w = w / len;

        return result;
    }

    Quaternion Quaternion::Conjugate() const
    {
        return Quaternion(
            -x,
            -y,
            -z,
            w
        );
    }

    Quaternion Quaternion::Inverse() const
    {
        return Conjugate() * (1.f / lengthSquared());
    }

    Quaternion Quaternion::FromAxisAngle(const Vec3& axis, float angle)
    {
        float rad = Math::DegToRad(angle);

        float half = rad / 2.f;

        float c = cos(half);
        float s = sin(half);

        Vec3 normalized = axis.Normalized();

        return Quaternion(
            normalized.x * s,
            normalized.y * s,
            normalized.z * s,
            c
        );
    }

    void Quaternion::rotate(const Vec3& axis, float angle)
    {
        *this *= FromAxisAngle(axis, angle);
    }

    Vec3 Quaternion::Rotate(const Vec3& vec) const
    {
        Quaternion vector(vec.x, vec.y, vec.z, 0);

        Quaternion result = *this * vector * Conjugate();

        return Vec3(
            result.x,
            result.y,
            result.z
        );
    }

    Mat4 Quaternion::ToMatrix() const
    {
        float xx = x * x;
        float yy = y * y;
        float zz = z * z;

        float xy = x * y;
        float xz = x * z;
        float yz = y * z;

        float wx = w * x;
        float wy = w * y;
        float wz = w * z;

        return Mat4(
            1 - 2 * (yy + zz), 2 * (xy + wz),     2 * (xz - wy),     0,
            2 * (xy - wz),     1 - 2 * (xx + zz), 2 * (yz + wx),     0,
            2 * (xz + wy),     2 * (yz - wx),     1 - 2 * (xx + yy), 0,
            0,                 0,                 0,                 1
        );
    }

    Quaternion Quaternion::Identity()
    {
        return Quaternion(0, 0, 0, 1);
    }
}