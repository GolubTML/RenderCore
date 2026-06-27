#pragma once

namespace rc
{
    struct Vec3;
    struct Vec4;

    struct Mat4
    {
        float data[4][4];

        Mat4();
        Mat4(float identity);
        Mat4(float m00, float m01, float m02, float m03,
             float m10, float m11, float m12, float m13,
             float m20, float m21, float m22, float m23,
             float m30, float m31, float m32, float m33);

        float* operator[](int index);
        const float* operator[](int index) const;

        Mat4 operator+(const Mat4& other) const;
        Mat4 operator-(const Mat4& other) const;

        Mat4 operator*(const Mat4& other) const;
        Vec4 operator*(const Vec4& vec) const;
        Mat4 operator*(float scalar) const;

        Mat4& operator=(const Mat4& other);

        static Mat4 Translate(const Mat4& model, const Vec3& position);
        static Mat4 Scale(const Mat4& model, const Vec3& size);
        
        static Mat4 RotateX(const Mat4& model, float angle);
        static Mat4 RotateY(const Mat4& model, float angle);
        static Mat4 RotateZ(const Mat4& model, float angle);

        static Mat4 LookAt(const Vec3& eye, const Vec3& target, const Vec3& up);

        static Mat4 Perspective(float fov, float aspect, float near, float far);
        static Mat4 Orthographic(float left, float right, float top, float bottom, float near, float far);

        Mat4 Transpose() const;
    };
}