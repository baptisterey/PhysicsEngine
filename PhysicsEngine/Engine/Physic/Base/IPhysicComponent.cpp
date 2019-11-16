#include "IPhysicComponent.h"

#include "../../Managers/SystemManager.h"
#include "../PhysicSystem.h"

IPhysicComponent::IPhysicComponent() : BaseComponent()
{
	PhysicSystem* physicSystem = SystemManager::GetSystemByType<PhysicSystem>();
	if (physicSystem != nullptr) {
		physicSystem->AddPhysicComponent(this);
	}
}

IPhysicComponent::~IPhysicComponent()
{
	PhysicSystem* physicSystem = SystemManager::GetSystemByType<PhysicSystem>();
	if (physicSystem != nullptr) {
		physicSystem->RemovePhysicComponent(this);
	}
}

void IPhysicComponent::SetMass(float _mass)
{
	mass = _mass;
	if (mass != 0) {
		invertedMass = 1 / _mass;
	}
	else {
		invertedMass = 0;
	}
}

float IPhysicComponent::GetMass() { return mass; }

float IPhysicComponent::GetInvertedMass() { return invertedMass; }


void IPhysicComponent::AddForceAtPoint( Vector3 & const force,  Vector3 & const point)
{
	accumForce = accumForce + force;

	Vector3 localPoint = GetOwner()->GetTransform()->WorldToLocal(point);
	Vector3 torqueToAdd = (Vector3::Cross(localPoint, force));

	accumTorque = accumTorque + torqueToAdd;
}

void IPhysicComponent::AddForceAtBodyPoint( Vector3 & const force,  Vector3 & const point)
{
	Vector3 worldPoint = GetOwner()->GetTransform()->LocalToWorld(point);
	AddForceAtPoint(force, worldPoint);
}

void IPhysicComponent::ClearAccumForce()
{
	accumForce = Vector3();
}

void IPhysicComponent::ClearAccumTorqueForce()
{
	accumTorque = Vector3();
}

Vector3 IPhysicComponent::GetVelocity()
{
	return velocity;
}

Vector3 IPhysicComponent::GetAcceleration()
{
	return acceleration;
}

void IPhysicComponent::SetVelocity(Vector3 value)
{
	velocity = value;
}