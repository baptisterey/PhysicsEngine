#include <vector>
#include "ISystem.h"
#include "SystemManager.h"
#include "LogicSystem.h"

int main(int argc, char* args[]) {

	
	bool running = true;

	LogicSystem* logicSystem = new LogicSystem();
	SystemManager::AddSystem(logicSystem);
	
	while (running) {
		
		for (ISystem* system : SystemManager::GetSystems()) {
			system->Update();
		}
		
	}
	
}