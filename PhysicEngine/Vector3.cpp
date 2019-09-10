#include "Vector3.h"

#include <math.h> 

Vector3::Vector3()
{
	x = 0;
	y = 0;
	z = 0;
}

Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

Vector3::~Vector3()
{

}


void Vector3::Normalize()
{
	float magnitude = GetMagnitude();

	x = x / magnitude;
	y = y / magnitude;
	z = z / magnitude;
}

float Vector3::GetMagnitude() const
{
	return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

Vector3 Vector3::operator+(Vector3 const& vect)
{
	return Vector3(x + vect.x, y + vect.y, z + vect.z);
}

Vector3 Vector3::operator+=(Vector3 const & vect)
{
	return Vector3(x + vect.x, y + vect.y, z + vect.z);
}

Vector3 Vector3::operator-(Vector3 const & vect)
{
	return Vector3(x - vect.x, y - vect.y, z - vect.z);
}

Vector3 Vector3::operator-=(Vector3 const & vect)
{
	return Vector3(x - vect.x, y - vect.y, z - vect.z);
}

Vector3 Vector3::operator/(float value)
{
	return Vector3(x / value, y / value, z / value);
}

Vector3 Vector3::operator*(float value)
{
	return Vector3(x * value, y * value, z * value);
}

bool Vector3::operator==(Vector3 const & vect)
{
	return (x == vect.x && y == vect.y && z == vect.z);
}

bool Vector3::operator!=(Vector3 const & vect)
{
	return (x != vect.x || y != vect.y || z != vect.z);
}

Vector3 Vector3::Cross(Vector3 const& a, Vector3 const& b)
{
	return Vector3( a.y * b.z - b.y * a.z, b.x * a.z - a.x * b.z, a.x * b.y - b.x * a.y);
}

float Vector3::Dot(Vector3 const & a, Vector3 const & b)
{
	return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

float Vector3::Distance(Vector3 const & a, Vector3 const & b)
{
	return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2) + pow(a.z - b.z, 2));
}

float Vector3::Angle(Vector3 const & a, Vector3 const & b)
{
	return acos(Vector3::Dot(a, b) / (a.GetMagnitude() * b.GetMagnitude()));
}
