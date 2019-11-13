#pragma once

#include "Base/IPhysicComponent.h"
#include "../Math/Quaternion.h"
#include "../Math/Vector3.h"
#include "./ForceGenerators/IForceGenerator.h"
#include "./ForceGenerators/Forces/GravityForce.h"

class RigidBody : public IPhysicComponent, public IForceGenerator
{
public:

	/// <summary>
	/// Construct a rigidbody based on a sphere of radius.
	/// </summary>
	RigidBody(float mass, float radius, float linearDamping, float angularDamping);

	/// <summary>
	/// Construct a rigidbody based on a box of dx, dy, dz.
	/// </summary>
	RigidBody(float mass, float dx, float dy, float dz, float linearDamping, float angularDamping);

	~RigidBody();

	void UpdatePhysics(float deltaTime);

	std::vector<IForce*> GetForces(float time);

	void SetGravity(bool value);
	bool GetGravity();

private:

	Matrix3 globalInverseInertialTensor;
	Matrix3 localInverseInertialTensor;
	float linearDamping, angularDamping;

	void SetLocalInverseInertialTensorFromSphere(float radius);
	void SetLocalInverseInertialTensformFromBox(float dx, float dy, float dz);

	bool gravity = true;
};
