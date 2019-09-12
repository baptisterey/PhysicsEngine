#pragma once
#include <vector>
#include "../Base/ISystem.h"

class SystemManager
{
public:
	static ISystem* AddSystem(ISystem* system);
	static std::vector<ISystem*> GetSystems();
	
	template<class SystemType>
	static SystemType* GetSystemByType() {
		for (auto && system : SystemManager::systems) {
			if (SystemType* t = dynamic_cast<SystemType*>(system)) {
				return t;
			}
		}

		return nullptr;
	}

private:
	static std::vector<ISystem*> systems;
};

