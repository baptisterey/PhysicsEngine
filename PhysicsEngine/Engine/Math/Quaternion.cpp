#include "Quaternion.h"

/// <summary>
/// Create a quaternion identity
/// </summary>
Quaternion::Quaternion()
{
	x = y = z = 0;
	w = 1;

	norme = 1;
}

/// <summary>
/// Create a quaternion from its values (w, x, y, z)
/// </summary>
/// <param name="_w"></param>
/// <param name="_x"></param>
/// <param name="_y"></param>
/// <param name="_z"></param>
Quaternion::Quaternion(float _w, float _x, float _y, float _z)
{
	w = _w;
	x = _x;
	y = _y;
	z = _z;

	norme = sqrt(w * w + x * x + y * y + z * z);
}

/// <summary>
/// Create a quaternion from a vector (x, y, z) and an angle w
/// </summary>
/// <param name="angle"></param>
/// <param name="axis"></param>
/// <returns></returns>
Quaternion Quaternion::fromAngleAndAxis(float angle, Vector3 axis)
{
	return Quaternion(angle, axis.x, axis.y, axis.z);
}

/// <summary>
/// Create a quaternion a matrix rotation (Euler angles in degrees)
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="z"></param>
/// <returns></returns>
Quaternion Quaternion::fromEulerAngles(float x, float y, float z)
{

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

/// <summary>
/// Returns quaternion conjuguate (x, y, z)
/// </summary>
/// <returns></returns>
Vector3 Quaternion::vector() const
{
	return Vector3(x, y, z);
}

/// <summary>
/// Normalize current quaternion
/// </summary>
/// <returns></returns>
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

/// <summary>
/// Return current quaternion conjugate (w, -x, -y, -z)
/// </summary>
/// <returns></returns>
Quaternion Quaternion::conjugated() const
{
	return Quaternion::fromAngleAndAxis(w, -vector());
}

/// <summary>
/// Rotates a vector through the current quaternion
/// </summary>
/// <param name="vector"></param>
/// <returns></returns>
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

/// <summary>
/// Convert current quaternion to a matrix rotation
/// </summary>
/// <param name="q"></param>
/// <returns></returns>
Matrix3 Quaternion::ToMatrix3(Quaternion const & q)
{
	double x = q.x;
	double y = q.y;
	double z = q.z;
	double w = q.w;

	double a = 1 - (2 * y*y - 2 * z*z);
	double b = 2 * x*y - 2 * z*w;
	double c = 2 * x*z + 2 * y*w;

	double d = 2 * x*y + 2 * z*w;
	double e = 1 - (2 * x*x - 2 * z*z);
	double f = 2 * y*z - 2 * x*w;

	double g = 2 * x*z - 2 * y*w;
	double h = 2 * y*z + 2 * x*w;
	double i = 1 - (2 * x*x - 2 * y*y);

	return Matrix3(
		a, b, c,
		d, e, f,
		g, h, i
	);
}

/// <summary>
/// Rotate current quaternion with a mtrix rotation (x, y, z) in radians
/// </summary>
/// <param name="q"></param>
/// <param name="vector"></param>
/// <returns></returns>
Quaternion Quaternion::RotateByVector(Quaternion const & q, Vector3 const & vector)
{
	// return q * Quaternion::fromEulerAngles(vector.x, vector.y, vector.z).normalize();
	Quaternion q2 = q * Quaternion(0, vector.x, vector.y, vector.z);
	return Quaternion(
		q2.w + q.w,
		q2.x + q.x,
		q2.y + q.y,
		q2.z + q.z
	).normalize();
}

std::string Quaternion::ToString()
{
	return "(w : " + std::to_string(w) + ", x : " + std::to_string(x) + ", y : " + std::to_string(y) + ", z : " + std::to_string(z) + ")";
}
