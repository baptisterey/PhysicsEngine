#pragma once

#include "Base/IPhysicComponent.h"
#include "../Math/Quaternion.h"
#include "../Math/Vector3.h"
//#include "../Math/Matrix3.h"
#include "../Math/Matrix4.h"

class RigidBody : public IPhysicComponent
{
public:

	RigidBody();
	RigidBody(Quaternion orientation, Vector3 rotation, float linearDamping, Vector3 vel, float mass);

	~RigidBody();

	void UpdatePhysics(float deltaTime);

	void addForceAtPoint(Vector3 force, Vector3 point);
	void addForceAtBodyPoint(Vector3 force, Vector3 point);
private:

	Quaternion orientation;
	Vector3 rotation;
	Matrix4 transformMatrix;
	Matrix3 inverseInertiaTensor;
	float linearDamping, angularDamping;
};
