#pragma once
#include "Vector3.h"
#include "Matrix3.h"

class Matrix4
{
public:

	//Constructor
    Matrix4();
    Matrix4(Matrix4& copyMatrix);
    Matrix4(float matrixTable[]);

	//Methode
    float matrix4Det();
    Matrix4 matrix4Inverse();
    Matrix4 matrix4Transpose();
	static Matrix4 PerspectiveFov(float FOV, float Aspect, float ZNear, float ZFar);
	static Matrix4 LookAt(const Vector3& Eye, const Vector3& At, const Vector3& Up);
	Vector3 TransformPoint(const Vector3& point) const;

	//Operator
	Matrix4 operator*(Matrix4 const& matrix);
    Vector3 operator*(Vector3 const& v);

	float matrix[16];
};