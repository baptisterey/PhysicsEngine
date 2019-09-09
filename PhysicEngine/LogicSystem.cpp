#include "LogicSystem.h"

LogicSystem::LogicSystem() : ISystem()
{

}


LogicSystem::~LogicSystem()
{

}

void LogicSystem::Update()
{
	for (ILogicComponent* component : components) {
		component->Update(0.33f); // TODO : Ajouter le time delta
	}
}

void LogicSystem::AddLogicComponent(ILogicComponent * component)
{
	if (component != nullptr) {
		components.push_back(component);
	}
}

void LogicSystem::RemoveLogicComponent(ILogicComponent * component)
{
	components.erase(std::remove(components.begin(), components.end(), component), components.end());
}
