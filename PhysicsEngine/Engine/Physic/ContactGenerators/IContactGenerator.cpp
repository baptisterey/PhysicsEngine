#include "IContactGenerator.h"

#include "../../Managers/SystemManager.h"
#include "../PhysicSystem.h"

IContactGenerator::IContactGenerator()
{
	PhysicSystem* physicSystem = SystemManager::GetSystemByType<PhysicSystem>();
	if (physicSystem != nullptr) {
		physicSystem->AddContactGenerator(this);
	}
}


IContactGenerator::~IContactGenerator()
{
	PhysicSystem* physicSystem = SystemManager::GetSystemByType<PhysicSystem>();
	if (physicSystem != nullptr) {
		physicSystem->AddContactGenerator(this);
	}
}
