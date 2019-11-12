#include "RigidBody.h"

RigidBody::RigidBody()
{
	SetMass(1);
	velocity = Vector3();
}

RigidBody::RigidBody(Quaternion orientation, Vector3 rotation, float linearDamping, Vector3 vel, float mass)
	: orientation(orientation), rotation(rotation), linearDamping(linearDamping)
{
	SetMass(mass);
	velocity = vel;
}

RigidBody::~RigidBody()
{
}

void RigidBody::UpdatePhysics(float deltaTime)
{
	//Position update
	if (GetInvertedMass() < 0 || deltaTime <= 0) {
		return;
	}

	GetOwner()->GetTransform()->SetPosition(GetOwner()->GetTransform()->GetPosition() + velocity * deltaTime); // Update position based on velocity
	acceleration = accumForce * GetInvertedMass();

	velocity = velocity + accumForce * deltaTime;

	//Rotation update
	GetOwner()->GetTransform()->SetRotation(GetOwner()->GetTransform()->GetRotation() + rotation * deltaTime);

	ClearAccumForce();
}

void RigidBody::addForceAtPoint(Vector3 force, Vector3 point)
{
}

void RigidBody::addForceAtBodyPoint(Vector3 force, Vector3 point)
{
}