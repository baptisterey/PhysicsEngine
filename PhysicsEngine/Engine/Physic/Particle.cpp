#include "Particle.h"
#include <math.h> 

#include "PhysicSystem.h"
#include <iostream>

#include "./ForceGenerators/DragForce.h"
#include "./ForceGenerators/GravityForce.h"
#include "../Managers/SystemManager.h"

Particle::Particle() : ILogicComponent(), IPhysicComponent()  {
	SetMass(1);
}


Particle::Particle(Vector3 vel, float mass) : ILogicComponent(), IPhysicComponent() {
	velocity = vel;
	SetMass(mass);
}

Particle::Particle(Vector3 vel, float mass, float kDrag1, float kDrag2) : kDrag1(kDrag1), kDrag2(kDrag2)
{
	velocity = vel;
	SetMass(mass);
}


Particle::~Particle() {

}

void Particle::Update(float deltaTime)
{
	PhysicSystem* physicSystem = SystemManager::GetSystemByType<PhysicSystem>();

	if (gravity) {
		physicSystem->AddForce(this, new GravityForce());
	}

	physicSystem->AddForce(this, new DragForce(kDrag1, kDrag2));
}

// Update is called once per frame
void Particle::UpdatePhysics(float deltaTime)
{
	if (GetInvertedMass() < 0 || deltaTime <= 0) {
		return;
	}

	GetOwner()->SetPosition( GetOwner()->GetPosition() + velocity * deltaTime); // Update position based on velocity
	acceleration = accumForce * GetInvertedMass();

	velocity = velocity + accumForce * deltaTime;

	ClearAccumForce();
}

void Particle::SetGravity(bool value)
{
	gravity = value;
}

bool Particle::IsAffectedByGravity()
{
	return gravity;
}

