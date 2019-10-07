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


void IPhysicComponent::AddForce(const Vector3 & value)
{
	accumForce = accumForce + value;
}

void IPhysicComponent::ClearAccumForce()
{
	accumForce = Vector3();
}

Vector3 IPhysicComponent::GetVelocity()
{
	return velocity;
}

Vector3 IPhysicComponent::GetAcceleration()
{
	return acceleration;
}

void IPhysicComponent::AddImpulse(Vector3 impulse)
{
	velocity = velocity + (impulse * GetInvertedMass());
}
