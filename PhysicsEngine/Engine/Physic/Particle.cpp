#include "Particle.h"
#include <math.h> 

#include "PhysicSystem.h"
#include <iostream>

#include "./ForceGenerators/Forces/DragForce.h"
#include "./ForceGenerators/Forces/GravityForce.h"
#include "../Managers/SystemManager.h"

Particle::Particle() : IPhysicComponent(), IForceGenerator() {
	SetMass(1);
	velocity = Vector3();
}


Particle::Particle(Vector3 vel, float mass) : IPhysicComponent(), IForceGenerator() {
	velocity = vel;
	SetMass(mass);
}

Particle::Particle(Vector3 vel, float mass, float kDrag1, float kDrag2) : kDrag1(kDrag1), kDrag2(kDrag2), IForceGenerator()
{
	velocity = vel;
	SetMass(mass);
}


Particle::~Particle() {

}

std::vector<IForce*> Particle::GetForces(float time)
{
	std::vector<IForce*> forces = std::vector<IForce*>();

	if (gravity) {
		forces.push_back( new GravityForce(this));
	}

	forces.push_back(new DragForce(this, kDrag1, kDrag2));

	return forces;
}


// Update is called once per frame
void Particle::UpdatePhysics(float deltaTime)
{
	if (GetInvertedMass() < 0 || deltaTime <= 0) {
		return;
	}

	GetOwner()->GetTransform()->SetPosition( GetOwner()->GetTransform()->GetPosition() + velocity * deltaTime); // Update position based on velocity
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

