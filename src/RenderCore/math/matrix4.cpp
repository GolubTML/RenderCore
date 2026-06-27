#include "RenderCore/math/matrix4.hpp"
#include "RenderCore/math/vector4.hpp"
#include "RenderCore/math/math.hpp"
#include <cassert>
#include <cmath>

namespace rc
{
    Mat4::Mat4()
    {
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                data[i][j] = 0;
    }

    Mat4::Mat4(float identity)
    {
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                data[i][j] = (i == j) ? identity : 0;
    }

    Mat4::Mat4(float m00, float m01, float m02, float m03,
               float m10, float m11, float m12, float m13,
               float m20, float m21, float m22, float m23,
               float m30, float m31, float m32, float m33)
    {
        data[0][0] = m00; data[0][1] = m01; data[0][2] = m02; data[0][3] = m03;
        data[1][0] = m10; data[1][1] = m11; data[1][2] = m12; data[1][3] = m13;
        data[2][0] = m20; data[2][1] = m21; data[2][2] = m22; data[2][3] = m23;
        data[3][0] = m30; data[3][1] = m31; data[3][2] = m32; data[3][3] = m33;
    }

    float* Mat4::operator[](int index)
    {
        assert(index >= 0 && index < 4);

        return data[index];
    }
    const float* Mat4::operator[](int index) const
    {
        assert(index >= 0 && index < 4);

        return data[index];
    }

    Mat4 Mat4::operator+(const Mat4& other) const
    {
        Mat4 result;

        for (int row = 0; row < 4; ++row)
            for (int col = 0; col < 4; ++col)
                result[row][col] = data[row][col] + other[row][col];

        return result;
    }
    Mat4 Mat4::operator-(const Mat4& other) const
    {
        Mat4 result;

        for (int row = 0; row < 4; ++row)
            for (int col = 0; col < 4; ++col)
                result[row][col] = data[row][col] - other[row][col];

        return result;
    }

    Mat4 Mat4::operator*(const Mat4& other) const
    {
        Mat4 result;

        for (int i = 0; i < 4; ++i)
        {
            float a0 = data[i][0];
            float a1 = data[i][1];
            float a2 = data[i][2];
            float a3 = data[i][3];

            result[i][0] = a0 * other[0][0] + a1 * other[1][0] + a2 * other[2][0] + a3 * other[3][0];
            result[i][1] = a0 * other[0][1] + a1 * other[1][1] + a2 * other[2][1] + a3 * other[3][1];
            result[i][2] = a0 * other[0][2] + a1 * other[1][2] + a2 * other[2][2] + a3 * other[3][2];
            result[i][3] = a0 * other[0][3] + a1 * other[1][3] + a2 * other[2][3] + a3 * other[3][3];
        }

        return result;
    }

    Vec4 Mat4::operator*(const Vec4& vec) const
    {
        Vec4 result;

        result[0] = data[0][0] * vec[0] + data[0][1] * vec[1] + data[0][2] * vec[2] + data[0][3] * vec[3];
        result[1] = data[1][0] * vec[0] + data[1][1] * vec[1] + data[1][2] * vec[2] + data[1][3] * vec[3];
        result[2] = data[2][0] * vec[0] + data[2][1] * vec[1] + data[2][2] * vec[2] + data[2][3] * vec[3];
        result[3] = data[3][0] * vec[0] + data[3][1] * vec[1] + data[3][2] * vec[2] + data[3][3] * vec[3];

        return result;
    }

    Mat4 Mat4::operator*(float scalar) const
    {
        Mat4 result;

        for (int i = 0; i < 4; ++i)
        {

            result[i][0] = data[i][0] * scalar;
            result[i][1] = data[i][1] * scalar;
            result[i][2] = data[i][2] * scalar;
            result[i][3] = data[i][3] * scalar;
        }

        return result;
    }

    Mat4& Mat4::operator=(const Mat4& other)
    {
        if (this == &other)
            return *this;

        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                data[i][j] = other[i][j];

        return *this;
    }

    Mat4 Mat4::Translate(const Mat4& model, const Vec3& position)
    {
        Mat4 translate(
            1, 0, 0, position.x,
            0, 1, 0, position.y,
            0, 0, 1, position.z,
            0, 0, 0, 1
        );

        return model * translate;
    }
    Mat4 Mat4::Scale(const Mat4& model, const Vec3& size)
    {
        Mat4 sizeMat(
            size.x, 0,      0,      0,
            0,      size.y, 0,      0,
            0,      0,      size.z, 0,
            0,      0,      0,      1
        );

        return model * sizeMat;
    }

    Mat4 Mat4::RotateX(const Mat4& model, float angle)
    {
        float rad = Math::DegToRad(angle);

        float cosAngle = cos(rad);
        float sinAngle = sin(rad);

        Mat4 rotated(
            1, 0,        0,         0,
            0, cosAngle, -sinAngle, 0,
            0, sinAngle, cosAngle,  0,
            0, 0,        0,         1
        );

        return model * rotated;
    }
    Mat4 Mat4::RotateY(const Mat4& model, float angle)
    {
        float rad = Math::DegToRad(angle);

        float cosAngle = cos(rad);
        float sinAngle = sin(rad);

        Mat4 rotated(
            cosAngle,  0, sinAngle,  0,
            0,         1, 0,         0,
            -sinAngle, 0, cosAngle,  0,
            0,         0, 0,         1
        );

        return model * rotated;
    }
    Mat4 Mat4::RotateZ(const Mat4& model, float angle)
    {
        float rad = Math::DegToRad(angle);

        float cosAngle = cos(rad);
        float sinAngle = sin(rad);

        Mat4 rotated(
            cosAngle, -sinAngle, 0,  0,
            sinAngle, cosAngle,  0,  0,
            0,        0,         1,  0,
            0,        0,         0,  1
        );

        return model * rotated;
    }

    Mat4 Mat4::LookAt(const Vec3& eye, const Vec3& target, const Vec3& up)
    {
        Vec3 z = eye - target;
        z.Normalize();

        Vec3 x = up.cross(z);
        x.Normalize();

        Vec3 y = z.cross(x);

        return Mat4(
            x.x, y.x, z.x, -(x.dot(eye)),
            x.y, y.y, z.y, -(y.dot(eye)),
            x.z, y.z, z.z, -(z.dot(eye)),
            0,   0,   0,   1
        );
    }

    Mat4 Mat4::Perspective(float fov, float aspect, float near, float far)
    {
        assert(aspect != 0); // may cause crash
        assert(far != near);

        float f = 1.f / tan(Math::DegToRad(fov) / 2.f);

        return Mat4(
            f / aspect, 0, 0, 0,
            0, f, 0, 0,
            0, 0, far / (near - far), (far * near) / (near - far),
            0, 0, -1, 0
        );
    }

    Mat4 Mat4::Orthographic(float left, float right, float top, float bottom, float near, float far)
    {
        return Mat4(
            2 / (right - left), 0, 0, -(right + left) / (right - left),
            0, 2 / (top - bottom), 0, -(top + bottom) / (top - bottom),
            0, 0, 2 / (near - far),   -(near + far) / (near - far),
            0, 0, 0, 1
        );
    }

    Mat4 Mat4::Transpose() const
    {
        Mat4 result;

        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                result[i][j] = data[j][i];

        return result;
    }
}