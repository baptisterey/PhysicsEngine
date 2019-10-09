#pragma once

#include "Vector3.h"
#include <math.h>

class Quaternion {
public:
	Quaternion();
	Quaternion(float _w, float _x, float _y, float _z);
	static Quaternion fromAngleAndAxis(float angle, Vector3 axis);
	static Quaternion fromEulerAngles(float x, float y, float z);
	Vector3 vector() const;
	Quaternion normalized() const;
	Quaternion conjugated() const;
	Vector3 rotatedVector(Vector3 vector);

	// ---- OPERATOR OVERLOADING ----
	Quaternion operator*(Quaternion const& q) const;
	Quaternion& operator*=(Quaternion const& q);
private:
	float x, y, z, w;
	float norme;
};