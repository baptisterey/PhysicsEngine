#pragma once
#include "Vector3.h"
#include "Matrix3.h"
#include <vector>

class Matrix4
{
public:
	/// <summary>
	/// Constructor (identity)
	/// </summary>
    Matrix4();

	/// <summary>
	/// Constructor from another matrix
	/// </summary>
	/// <param name="copyMatrix"></param>
    Matrix4(Matrix4& copyMatrix);

	/// <summary>
	/// Constructor from an array a values
	/// </summary>
	/// <param name="matrixTable"></param>
    Matrix4(std::vector<float> matrixTable);



	/// <summary>
	/// Returns matrix determinant
	/// </summary>
	/// <returns></returns>
    float matrix4Det();

	/// <summary>
	/// Returns inverted matrix
	/// </summary>
	/// <returns></returns>
    Matrix4 matrix4Inverse();

	/// <summary>
	/// Returns transposed matrix
	/// </summary>
	/// <returns></returns>
    Matrix4 matrix4Transpose();

	/// <summary>
	/// Returns a projection matrix for the given parameters
	/// </summary>
	/// <param name="FOV">Angles of the FOV</param>
	/// <param name="Aspect">Aspect raio (width/height)</param>
	/// <param name="ZNear">Distance to the near plane of the camera</param>
	/// <param name="ZFar">Distance to the far plane of the camera</param>
	/// <returns></returns>
	static Matrix4 PerspectiveFov(float FOV, float Aspect, float ZNear, float ZFar);

	/// <summary>
	/// Returns a matrix rotation to rotate towards looking to a point
	/// </summary>
	/// <param name="Eye">Current direction the eye is looking at (or current rotation)</param>
	/// <param name="At">Point we want to look at</param>
	/// <param name="Up">Current local UP vector</param>
	/// <returns></returns>
	static Matrix4 LookAt(const Vector3& Eye, const Vector3& At, const Vector3& Up);

	/// <summary>
	/// Apply the current matrix rotation to a point
	/// </summary>
	/// <param name="point"></param>
	/// <returns></returns>
	Vector3 TransformPoint(const Vector3& point) const;

	/// <summary>
	/// Conversion to give the matrix to a GLSL shader
	/// </summary>
	/// <param name="temp"></param>
	void getTransformedMatrix(float temp[4][4]);


	// ---- OPERATOR OVERLOADING ----
	Matrix4 operator*(Matrix4 const& matrix);
    Vector3 operator*(Vector3 const& v);
	// ------------------------------


	/// <summary>
	/// Matrix values
	/// </summary>
	std::vector<float> matrix;
};
