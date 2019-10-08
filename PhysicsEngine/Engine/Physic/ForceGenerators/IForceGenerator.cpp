#include "IForceGenerator.h"

#include "../../Managers/SystemManager.h"
#include "../PhysicSystem.h"


IForceGenerator::IForceGenerator()
{
	PhysicSystem* physicSystem = SystemManager::GetSystemByType<PhysicSystem>();
	if (physicSystem != nullptr) {
		physicSystem->AddForceGenerator(this);
	}
}

IForceGenerator::~IForceGenerator()
{
	PhysicSystem* physicSystem = SystemManager::GetSystemByType<PhysicSystem>();
	if (physicSystem != nullptr) {
		physicSystem->AddForceGenerator(this);
	}
}
