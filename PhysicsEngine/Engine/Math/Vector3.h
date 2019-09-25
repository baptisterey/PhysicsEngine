#pragma once
#include <iostream>

class Vector3
{

public:

	float x, y, z;

	Vector3();
	Vector3(float x, float y, float z);

	~Vector3();

	void Normalize();

	float GetSquaredMagnitude() const;
	float GetMagnitude() const;

	std::string ToString();


	// ---- OPERATOR OVERLOADING ----
	Vector3 operator+ (Vector3 const& vect);
	Vector3 operator+= (Vector3 const& vect);

	Vector3 operator- (Vector3 const& vect);
	Vector3 operator-= (Vector3 const& vect);

	Vector3 operator* (Vector3 const& vect);

	Vector3 operator/ (float value);
	Vector3 operator* (float value);

	bool operator== (Vector3 const& vect);
	bool operator!= (Vector3 const& vect);

	// ------------------------------

	static Vector3 Cross(Vector3 const& a, Vector3 const& b);
	static float Dot(Vector3 const& a, Vector3 const& b);
	static Vector3 Components(Vector3 const& a, Vector3 const& b);

	static float Distance(Vector3 const& a, Vector3 const& b);
	static float Angle(Vector3 const& a, Vector3 const& b);

	static Vector3 Normalized(Vector3 const& a);
	
	static Vector3 Abs(Vector3 const& a);
};
