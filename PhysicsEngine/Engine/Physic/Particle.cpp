#include "Particle.h"
#include <math.h> 

#include "PhysicSystem.h"
#include <iostream>

Particle::Particle() : IPhysicComponent(), BaseComponent(), velocity(Vector3()), damping(1) {
	SetMass(1);
}


Particle::Particle(Vector3 vel, float mass, float damping) : velocity(vel), damping(damping) {
	SetMass(mass);
}


Particle::~Particle() {

}

void Particle::SetMass(float _mass)
{
	mass = _mass;
	invertedMass = 1 / _mass;
}

float Particle::GetMass() { return mass; }

float Particle::GetInvertedMass() { return invertedMass; }

// Update is called once per frame
void Particle::Update(float deltaTime)
{
	GetOwner()->SetPosition( GetOwner()->GetPosition() + velocity * deltaTime); // Update position based on velocity
	velocity = velocity * pow(damping, deltaTime) + Vector3(0, PhysicSystem::GRAVITY_CONST, 0)  * deltaTime; // Update velocity based on damping and acceleration
}