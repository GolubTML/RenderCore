#pragma once

#include "vector3D.hpp"
#include "matrix4.hpp"

namespace rc
{
    struct Quaternion
    {
        float x;
        float y;
        float z;
        float w;

        Quaternion() : x(0), y(0), z(0), w(1) { }
        constexpr Quaternion(float x, float y, float z, float w)
            : x(x), y(y), z(z), w(w) { }

        Quaternion operator+(const Quaternion& other) const;
        Quaternion operator-(const Quaternion& other) const;

        Quaternion operator*(const Quaternion& other) const;
        Quaternion operator*(float scalar) const;

        Quaternion& operator+=(const Quaternion& other);
        Quaternion& operator-=(const Quaternion& other);
        Quaternion& operator*=(const Quaternion& other);

        float length() const;
        float lengthSquared() const;

        void Normalize();
        Quaternion Normalized() const;

        Quaternion Conjugate() const;
        Quaternion Inverse() const;

        static Quaternion FromAxisAngle(const Vec3& axis, float angle);

        void rotate(const Vec3& axis, float angle);
        Vec3 Rotate(const Vec3& vec) const;

        Mat4 ToMatrix() const;

        static Quaternion Identity();
    };
}