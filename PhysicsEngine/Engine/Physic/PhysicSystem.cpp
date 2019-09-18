#include "PhysicSystem.h"
#include "ForceGenerators/GravityForce.h"

PhysicSystem::PhysicSystem() : ISystem()
{

}


PhysicSystem::~PhysicSystem()
{

}

void PhysicSystem::Update()
{
	// Register all constant forces (gravity and damping) for all particles
	for (IPhysicComponent* component : components) {
		ForceRegister* gravityForceRegister = new ForceRegister(component, new GravityForce());
		forcesRegister.push_back(gravityForceRegister);
	}

	// Update all forces
	for (ForceRegister* force : forcesRegister) {
		force->forceGenerator->UpdateForce(force->physicComponent, Time::deltaTime);
	}

	// We update every physic components
	for (IPhysicComponent* component : components) {
		component->Update(Time::deltaTime);
	}

	// We clear all forces for this frame
	forcesRegister.clear();
}

void PhysicSystem::AddPhysicComponent(IPhysicComponent * component)
{
	if (component != nullptr) {
		components.push_back(component);
	}
}

void PhysicSystem::RemovePhysicComponent(IPhysicComponent * component)
{
	components.erase(std::remove(components.begin(), components.end(), component), components.end());
}
