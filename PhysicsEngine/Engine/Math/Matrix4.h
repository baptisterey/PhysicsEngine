#pragma once

#include "Vector3.h"
#include <string>
#include <iostream>
#include <GL\glew.h>
#include <SDL_opengl.h>
#include <sstream>
#include <math.h>

/*
Matrix4.h
Originaly written by Matthew Fisher
Edited by Yoann Haffner

a 4x4 transformation matrix structure.
*/

class Matrix4
{
public:
	//
	// Initalization
	//
	Matrix4();
	Matrix4(const Matrix4& M);
	Matrix4(const Vector3& V0, const Vector3& V1, const Vector3& V2);

#ifdef USE_D3D
	Matrix4(const D3DXMATRIX& M);
#endif

	//
	// Assignment
	//
	Matrix4& operator = (const Matrix4& M);

	//
	// Math properties
	//
	float Determinant() const;
	Matrix4 Transpose() const;
	Matrix4 Inverse() const;

	//
	// Vector transforms
	//
	__forceinline Vector3 TransformPoint(const Vector3& point) const
	{
		float w = point.x * _Entries[0][3] + point.y * _Entries[1][3] + point.z * _Entries[2][3] + _Entries[3][3];
		if (w)
		{
			const float invW = 1.0f / w;
			return Vector3((point.x * _Entries[0][0] + point.y * _Entries[1][0] + point.z * _Entries[2][0] + _Entries[3][0]) * invW,
				(point.x * _Entries[0][1] + point.y * _Entries[1][1] + point.z * _Entries[2][1] + _Entries[3][1]) * invW,
				(point.x * _Entries[0][2] + point.y * _Entries[1][2] + point.z * _Entries[2][2] + _Entries[3][2]) * invW);
		}
		else
		{
			return Vector3(0,0,0);
		}
	}

	__forceinline Vector3 TransformNormal(const Vector3& normal) const
	{
		return Vector3(normal.x * _Entries[0][0] + normal.y * _Entries[1][0] + normal.z * _Entries[2][0],
			normal.x * _Entries[0][1] + normal.y * _Entries[1][1] + normal.z * _Entries[2][1],
			normal.x * _Entries[0][2] + normal.y * _Entries[1][2] + normal.z * _Entries[2][2]);
	}

	//
	// Formatting
	//
	std::string CommaSeparatedString() const;
	std::string CommaSeparatedStringSingleLine() const;
	std::string SpaceSeperatedStringSingleLine() const;
	std::string TabSeperatedString() const;

#ifdef USE_D3D
	operator D3DXMATRIX() const;
#endif

	//
	// Accessors
	//
	__forceinline float* operator [] (int Row)
	{
		return _Entries[Row];
	}
	__forceinline const float* operator [] (int Row) const
	{
		return _Entries[Row];
	}
	__forceinline void SetColumn(GLuint Column, const float* Values, GLbyte RowCount)
	{
		if (RowCount > 4) RowCount = 4;
		for (;RowCount > 0; RowCount--)
			_Entries[RowCount - 1][Column] = Values[RowCount - 1];
	}
	__forceinline void SetRow(GLuint Row, const float* Values, GLbyte nbRow)
	{
		if (nbRow > 4) nbRow = 4;
		for (;nbRow > 0; nbRow--)
			_Entries[Row][nbRow - 1] = Values[nbRow - 1];
	}
	__forceinline float* GetColumn(GLuint Column)
	{
		float Result[4];
		Result[0] = _Entries[0][Column];
		Result[1] = _Entries[1][Column];
		Result[2] = _Entries[2][Column];
		Result[3] = _Entries[3][Column];
		return Result;
	}
	__forceinline float* GetRow(GLuint Row)
	{
		float Result[4];
		Result[0] = _Entries[Row][0];
		Result[1] = _Entries[Row][1];
		Result[2] = _Entries[Row][2];
		Result[3] = _Entries[Row][3];
		return Result;
	}

	//
	// Transformation matrices
	//
	static Matrix4 Identity();
	static Matrix4 Scaling(const Vector3& ScaleFactors);
	static Matrix4 Scaling(float ScaleFactor)
	{
		return Scaling(Vector3(ScaleFactor, ScaleFactor, ScaleFactor));
	}
	static Matrix4 Translation(const Vector3& Pos);
	static Matrix4 Rotation(const Vector3& Axis, float Angle, const Vector3& Center);
	static Matrix4 Rotation(const Vector3& Axis, float Angle);
	static Matrix4 Rotation(float Yaw, float Pitch, float Roll);
	static Matrix4 Rotation(const Vector3& Basis1, const Vector3& Basis2, const Vector3& Basis3);
	static Matrix4 RotationX(float Theta);
	static Matrix4 RotationY(float Theta);
	static Matrix4 RotationZ(float Theta);
	static Matrix4 Camera(const Vector3& Eye, const Vector3& Look, const Vector3& Up, const Vector3& Right);
	static Matrix4 LookAt(const Vector3& Eye, const Vector3& At, const Vector3& Up);
	static Matrix4 Orthogonal(float Width, float Height, float ZNear, float ZFar);
	static Matrix4 Perspective(float Width, float Height, float ZNear, float ZFar);
	static Matrix4 PerspectiveFov(float FOV, float Aspect, float ZNear, float ZFar);
	static Matrix4 PerspectiveMultiFov(float FovX, float FovY, float ZNear, float ZFar);
	static Matrix4 Face(const Vector3& V0, const Vector3& V1);
	static Matrix4 Viewport(float Width, float Height);
	static Matrix4 ChangeOfBasis(const Vector3& Source0, const Vector3& Source1, const Vector3& Source2, const Vector3& SourceOrigin,
		const Vector3& Target0, const Vector3& Target1, const Vector3& Target2, const Vector3& TargetOrigin);
	static float CompareMatrices(const Matrix4& Left, const Matrix4& Right);

private:
	float _Entries[4][4];
};

//
// Overloaded operators
//
Matrix4 operator * (const Matrix4& Left, const Matrix4& Right);
Matrix4 operator * (const Matrix4& Left, float& Right);
Matrix4 operator * (float& Left, const Matrix4& Right);
Matrix4 operator + (const Matrix4& Left, const Matrix4& Right);
Matrix4 operator - (const Matrix4& Left, const Matrix4& Right);

__forceinline float* operator * (const float*& Right, const Matrix4& Left)
{
	float f[] = { Right[0] * Left[0][0] + Right[1] * Left[1][0] + Right[2] * Left[2][0] + Right[3] * Left[3][0],
		Right[0] * Left[0][1] + Right[1] * Left[1][1] + Right[2] * Left[2][1] + Right[3] * Left[3][1],
		Right[0] * Left[0][2] + Right[1] * Left[1][2] + Right[2] * Left[2][2] + Right[3] * Left[3][2],
		Right[0] * Left[0][3] + Right[1] * Left[1][3] + Right[2] * Left[2][3] + Right[3] * Left[3][3] };
	return f;
}