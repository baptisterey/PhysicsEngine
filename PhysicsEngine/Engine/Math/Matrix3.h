#pragma once
#include "Vector3.h"
#include <vector>

class Matrix3
{
public:
	/// <summary>
	/// Constructor (identity)
	/// </summary>
	Matrix3();

	/// <summary>
	/// Constructor from a complete array a float
	/// </summary>
	/// <param name="matrixTable"></param>
    Matrix3(std::vector<float> matrixTable);

	/// <summary>
	/// Constructor from indexed values
	/// </summary>
	/// <param name="i0"></param>
	/// <param name="i1"></param>
	/// <param name="i2"></param>
	/// <param name="i3"></param>
	/// <param name="i4"></param>
	/// <param name="i5"></param>
	/// <param name="i6"></param>
	/// <param name="i7"></param>
	/// <param name="i8"></param>
    Matrix3(float i0, float i1, float i2, float i3, float i4, float i5, float i6, float i7, float i8);

	/// <summary>
	/// Constructor from existing matrix
	/// </summary>
	/// <param name="copyMatrix"></param>
    Matrix3(Matrix3& copyMatrix);



	/// <summary>
	/// Returns matrix determinant
	/// </summary>
	/// <returns></returns>
    float matrix3Det();

	/// <summary>
	/// Returns inverted matrix
	/// </summary>
	/// <returns></returns>
    Matrix3 matrix3Inverse();

	/// <summary>
	/// Returns transposed matrix
	/// </summary>
	/// <returns></returns>
    Matrix3 matrix3Transpose();
	

	// ---- OPERATOR OVERLOADING ----
	Vector3 operator*(Vector3 const& v);
	Matrix3 operator*(Matrix3 const& matrix);
	Matrix3 operator*(float value);
	// ------------------------------

	/// <summary>
	/// Matrix values
	/// </summary>
	std::vector<float> matrix;
};
