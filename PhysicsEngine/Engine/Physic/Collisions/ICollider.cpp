#include "ICollider.h"
#include "../PhysicSystem.h"

ICollider::ICollider()
{
	PhysicSystem* physicSystem = SystemManager::GetSystemByType<PhysicSystem>();
	if (physicSystem != nullptr) {
		physicSystem->AddColliderComponent(this);
	}
}

ICollider::~ICollider()
{
	PhysicSystem* physicSystem = SystemManager::GetSystemByType<PhysicSystem>();
	if (physicSystem != nullptr) {
		physicSystem->RemoveColliderComponent(this);
	}
}

float ICollider::GetBroadRadius()
{
	return broadRadius;
}