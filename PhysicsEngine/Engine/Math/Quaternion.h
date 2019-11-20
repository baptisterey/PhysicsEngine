#pragma once

#include "Vector3.h"
#include <math.h>
#include <string>

#include "Matrix3.h"

class Quaternion {
public:
	/// <summary>
	/// Create a quaternion identity
	/// </summary>
	Quaternion();

	/// <summary>
	/// Create a quaternion from its values (w, x, y, z)
	/// </summary>
	Quaternion(float _w, float _x, float _y, float _z);

	/// <summary>
	/// Create a quaternion from a vector (x, y, z) and an angle w
	/// </summary>
	static Quaternion fromAngleAndAxis(float angle, Vector3 axis);

	/// <summary>
	/// Create a quaternion a matrix rotation (Euler angles in degrees)
	/// </summary>
	static Quaternion fromEulerAngles(float x, float y, float z);

	/// <summary>
	/// Returns quaternion conjuguate (x, y, z)
	/// </summary>
	Vector3 vector() const;

	/// <summary>
	/// Normalize current quaternion
	/// </summary>
	Quaternion& normalize();

	/// <summary>
	/// Return current quaternion conjugate (w, -x, -y, -z)
	/// </summary>
	Quaternion conjugated() const;

	/// <summary>
	/// Rotates a vector through the current quaternion
	/// </summary>
	Vector3 rotatedVector(Vector3 vector);

	// ---- OPERATOR OVERLOADING ----
	Quaternion operator*(Quaternion const& q) const;
	Quaternion& operator*=(Quaternion const& q);
	// ------------------------------

	/// <summary>
	/// Convert current quaternion to a matrix rotation
	/// </summary>
	static Matrix3 ToMatrix3(Quaternion const& q);

	/// <summary>
	/// Rotate current quaternion with a mtrix rotation (x, y, z) in radians
	/// </summary>
	static Quaternion RotateByVector(Quaternion const& q, Vector3 const & vector);

	std::string ToString();

private:
	float x, y, z, w;
	float norme;
};