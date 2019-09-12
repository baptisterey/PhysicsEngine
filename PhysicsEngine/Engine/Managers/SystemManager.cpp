#include "SystemManager.h"

std::vector<ISystem*> SystemManager::systems = {};

ISystem * SystemManager::AddSystem(ISystem * system)
{
	if (system != nullptr) {
		SystemManager::systems.push_back(system);
	}

	return system;
}

std::vector<ISystem*> SystemManager::GetSystems()
{
	return systems;
}

