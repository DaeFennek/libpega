#pragma once

namespace math {
// The elements of the 3x4 matrix are stored in
// row-major order.
class Matrix3x4 {
public:
    Matrix3x4() = default;
    explicit Matrix3x4(bool zero);
    Matrix3x4(float m34[3][4]);
    Matrix3x4(float m00, float m01, float m02, float m03,
            float m10, float m11, float m12, float m13,
            float m20, float m21, float m22, float m23);
    ~Matrix3x4() = default;
    Matrix3x4(const Matrix3x4&) = default;
    Matrix3x4& operator = (const Matrix3x4&) = default;
    Matrix3x4(Matrix3x4&&) = default;
    Matrix3x4& operator = (Matrix3x4&&) = default;
    Matrix3x4 operator * (const Matrix3x4& other);

    void Scale(float x, float y, float z);
    void Translate(float x, float y, float z);
    void Rotate(const char axis, float degree);

    void SetIdentity();
    void SetZero();
public:
    float mMtx34[3][4];
};
}
