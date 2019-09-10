#include "PhysicSystem.h"

PhysicSystem::PhysicSystem() : ISystem()
{

}


PhysicSystem::~PhysicSystem()
{

}

void PhysicSystem::Update()
{
	for (IPhysicComponent* component : components) {
		component->Update(Time::deltaTime);
	}
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
