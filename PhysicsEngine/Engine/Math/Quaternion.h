#pragma once

#include "Vector3.h"
#include <math.h>

#include "Matrix3.h"

class Quaternion {
public:
	Quaternion();
	Quaternion(float _w, float _x, float _y, float _z);
	static Quaternion fromAngleAndAxis(float angle, Vector3 axis);
	static Quaternion fromEulerAngles(float x, float y, float z);
	Vector3 vector() const;
	Quaternion& normalize();
	Quaternion conjugated() const;
	Vector3 rotatedVector(Vector3 vector);

	// ---- OPERATOR OVERLOADING ----
	Quaternion operator*(Quaternion const& q) const;
	Quaternion& operator*=(Quaternion const& q);
	// ------------------------------

	static Matrix3 ToMatrix3(Quaternion const& q);
	static Quaternion RotateByVector(Quaternion const& q, Vector3 const & vector);

private:
	float x, y, z, w;
	float norme;
};