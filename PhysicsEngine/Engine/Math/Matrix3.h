#pragma once
#include "Vector3.h"
#include <vector>

class Matrix3
{
public:

	//Constructor
	Matrix3();
    Matrix3(std::vector<float> matrixTable);
    Matrix3(float i0, float i1, float i2, float i3, float i4, float i5, float i6, float i7, float i8);
    Matrix3(Matrix3& copyMatrix);

	//Methode
    float matrix3Det();
    Matrix3 matrix3Inverse();
    Matrix3 matrix3Transpose();
	
	//Operator
	Vector3 operator*(Vector3 const& v);
	Matrix3 operator*(Matrix3 const& matrix);
	Matrix3 operator*(float value);

	float matrix[9];
};
