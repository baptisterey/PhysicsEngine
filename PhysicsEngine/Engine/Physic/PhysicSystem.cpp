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
	// Update all forces
	for (ForceRegister* force : forcesRegister) {
		force->forceGenerator->UpdateForce(force->physicComponent, Time::deltaTime);
	}

	// We update every physic components
	for (IPhysicComponent* component : components) {
		component->UpdatePhysics(Time::deltaTime);
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

void PhysicSystem::AddForce(IPhysicComponent * component, IForceGenerator * force)
{
	forcesRegister.push_back(new ForceRegister(component, force));
}
