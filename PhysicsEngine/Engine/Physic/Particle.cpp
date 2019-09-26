#include "Particle.h"
#include <math.h> 

#include "PhysicSystem.h"
#include <iostream>

Particle::Particle() : IPhysicComponent() {
	SetMass(1);
}


Particle::Particle(Vector3 vel, float mass) : IPhysicComponent() {
	velocity = vel;
	SetMass(mass);
}


Particle::~Particle() {

}

// Update is called once per frame
void Particle::Update(float deltaTime)
{
	if (GetInvertedMass() < 0 || deltaTime <= 0) {
		return;
	}

	GetOwner()->SetPosition( GetOwner()->GetPosition() + velocity * deltaTime); // Update position based on velocity
	acceleration = accumForce * GetInvertedMass();

	velocity = velocity + accumForce * deltaTime;

	ClearAccumForce();
}

