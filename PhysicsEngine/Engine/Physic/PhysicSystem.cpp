#include "PhysicSystem.h"
#include "ForceGenerators/GravityForce.h"
#include "ForceGenerators/DragForce.h"

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

		ForceRegister* dragForceRegister = new ForceRegister(component, new DragForce(1, 0));
		forcesRegister.push_back(dragForceRegister);
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
	for (auto forceRegister : forcesRegister)
	{
		delete forceRegister;
	}
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
