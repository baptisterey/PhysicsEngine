#include "IPhysicComponent.h"

#include "SystemManager.h"
#include "PhysicSystem.h"

IPhysicComponent::IPhysicComponent()
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
