#include "Quaternion.h"

Quaternion::Quaternion()
{
	x = y = z = 0;
	w = 1;

	norme = 1;
}

Quaternion::Quaternion(float _w, float _x, float _y, float _z)
{
	w = _w;
	x = _x;
	y = _y;
	z = _z;
	norme = sqrt(w * w + x * x + y * y + z * z);
}

Quaternion Quaternion::fromAngleAndAxis(float angle, Vector3 axis)
{
	return Quaternion(angle, axis.x, axis.y, axis.z);
}

Quaternion Quaternion::fromEulerAngles(float x, float y, float z)
{
	// Code inspired by https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles
	// Abbreviations for the various angular functions
	double cy = cos(z * 0.5);
	double sy = sin(z * 0.5);
	double cp = cos(y * 0.5);
	double sp = sin(y * 0.5);
	double cr = cos(x * 0.5);
	double sr = sin(x * 0.5);

	return Quaternion(
		cy * cp * cr + sy * sp * sr,
		cy * cp * sr - sy * sp * cr,
		sy * cp * sr + cy * sp * cr,
		sy * cp * cr - cy * sp * sr
	);
}

Vector3 Quaternion::vector() const
{
	return Vector3(x, y, z);
}

Quaternion Quaternion::normalized() const
{
	return Quaternion(w / norme, x / norme, y / norme, z / norme);
}

Quaternion Quaternion::conjugated() const
{
	return Quaternion::fromAngleAndAxis(w, -vector());
}

Vector3 Quaternion::rotatedVector(Vector3 vector)
{
	// ret QR * QV * QR'
	// QR: rotation; QV: vector; QR': reverse rotation
	Quaternion
		a = (*this),
		b = Quaternion::fromAngleAndAxis(0, vector),
		c = (*this).conjugated(),
		d = a * b * c;
	return d.vector();
}

Quaternion Quaternion::operator*(Quaternion const& q) const
{
	Vector3 v0(x, y, z), v1(q.x, q.y, q.z);
	Quaternion qr = Quaternion::fromAngleAndAxis(
		w * q.w - Vector3::Dot(v0, v1),
		v1 * w + v0 * q.w + Vector3::Cross(v0, v1)
	);
	return qr;
}

Quaternion& Quaternion::operator*=(Quaternion const& q)
{
	Vector3 v0(x, y, z), v1(q.x, q.y, q.z);
	Vector3 vf = v1 * w + v0 * q.w + Vector3::Cross(v0, v1);

	w = w * q.w - Vector3::Dot(v0, v1);
	x = vf.x;
	y = vf.y;
	z = vf.z;
	norme = sqrt(w * w + x * x + y * y + z * z);
	return (*this);
}

Matrix3 Quaternion::ToMatrix3(Quaternion const & q)
{
	// Precalculate coordinate products
	float x = q.x * 2.0F;
	float y = q.y * 2.0F;
	float z = q.z * 2.0F;
	float xx = q.x * x;
	float yy = q.y * y;
	float zz = q.z * z;
	float xy = q.x * y;
	float xz = q.x * z;
	float yz = q.y * z;
	float wx = q.w * x;
	float wy = q.w * y;
	float wz = q.w * z;

	// Calculate 3x3 matrix from orthonormal basis
	Matrix3 m;
	m.matrix[0] = 1.0f - (yy + zz); m.matrix[1] = xy + wz; m.matrix[2] = xz - wy;
	m.matrix[3] = xy - wz; m.matrix[4] = 1.0f - (xx + zz); m.matrix[5] = yz + wx;
	m.matrix[6] = xz + wy; m.matrix[7] = yz - wx; m.matrix[8] = 1.0f - (xx + yy);

	return m;
}

Quaternion Quaternion::RotateByVector(Quaternion const & q, Vector3 const & vector)
{
	Quaternion
		a = q,
		b = Quaternion::fromAngleAndAxis(0, vector),
		c = q.conjugated(),
		d = a * b * c;
	return d;
}
