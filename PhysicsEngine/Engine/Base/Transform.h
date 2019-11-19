#pragma once

#include "../Math/Vector3.h"
#include "../Math/Quaternion.h"

#include "../Math/Matrix4.h"

class Transform
{
public:

	Transform();
	~Transform();

	/// <summary>
	/// Return the current position of the transform.
	/// </summary>
	/// <returns>The position of the transform.</returns>
	Vector3 GetPosition();

	/// <summary>
	/// Set the position of the transform with the given value.
	/// </summary>
	/// <param name="value">The value to be set.</param>
	void SetPosition(Vector3& const value);

	/// <summary>
	/// Get the current rotation of the transform.
	/// </summary>
	/// <returns>The rotation of the transform as Quaternion.</returns>
	Quaternion GetRotation();

	/// <summary>
	/// Set the rotation of the transform with the given value.
	/// </summary>
	/// <param name="value">The value (quaternion) to be set.</param>
	void SetRotation(Quaternion& const value);

	/// <summary>
	/// Convert the position form world space to local space.
	/// </summary>
	/// <param name="value">The value to convert.</param>
	/// <returns>The position relative to the transform.</returns>
	Vector3 WorldToLocal(Vector3& const value);

	/// <summary>
	/// Convert the position from local space to world space.
	/// </summary>
	/// <param name="value">The value to convert.</param>
	/// <returns>The world position.</returns>
	Vector3 LocalToWorld(Vector3& const value);

	/// <summary>
	/// Get the transform matrix (rotation) of this transform
	/// </summary>
	/// <returns></returns>
	Matrix3 GetTransformMatrix();


private:
	
	Vector3 position;
	Quaternion rotation = Quaternion(1, 0, 0, 0);

	Matrix3 transformMatrix;
};
