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

	float c1 = cos(z * 0.5f);
	float c2 = cos(x * 0.5f);
	float c3 = cos(y * 0.5f);

	float s1 = sin(z * 0.5f);
	float s2 = sin(x * 0.5f);
	float s3 = sin(y * 0.5f);

	return Quaternion(
		c1 * c2 * c3 - s1 * s2 * s3,
		s1 * s2 * c3 + c1 * c2 * s3,
		s1 * c2 * c3 + c1 * s2 * s3,
		c1 * s2 * c3 - s1 * c2 * s3
	);
}

Vector3 Quaternion::vector() const
{
	return Vector3(x, y, z);
}

Quaternion& Quaternion::normalize()
{
	float d = w * w + x * x + y * y + z * z;
	if (d == 0) {
		w = 1;
		x = 0;
		y = 0;
		z = 0;
	}
	else {

		d = 1 / sqrt(d);

		w = w * d;
		x = x * d;
		y = y * d;
		z = z * d;
	}
	return (*this);
}

Quaternion Quaternion::conjugated() const
{
	return Quaternion::fromAngleAndAxis(w, -vector());
}

Vector3 Quaternion::rotatedVector(Vector3 vector)
{
	if (vector.x == vector.y && vector.x == vector.z && vector.x == 0)
		return Vector3(0, 0, 0);

	// ret QR * QV * QR'
	// QR: rotation; QV: vector; QR': reverse rotation
	normalize();
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
	double x = q.x;
	double y = q.y;
	double z = q.z;
	double w = q.w;

	double a = 1 - (2 * y*y + 2 * z*z);
	double b = 2 * x*y + 2 * z*w;
	double c = 2 * x*z - 2 * y*w;

	double d = 2 * x*y - 2 * z*w;
	double e = 1 - (2 * x*x + 2 * z*z);
	double f = 2 * y*z + 2 * x*w;

	double g = 2 * x*z + 2 * y*w;
	double h = 2 * y*z - 2 * x*w;
	double i = 1 - (2 * x*x + 2 * y*y);

	return Matrix3(
		a, b, c,
		d, e, f,
		g, h, i
	);
}

Quaternion Quaternion::RotateByVector(Quaternion const & q, Vector3 const & vector)
{
	Quaternion q2 = Quaternion::fromEulerAngles(vector.x, vector.y, vector.z);
	return (q * q2).normalize();
}
