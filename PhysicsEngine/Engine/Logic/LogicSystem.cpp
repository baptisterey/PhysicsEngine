#include "LogicSystem.h"

LogicSystem::LogicSystem() : ISystem()
{

}


LogicSystem::~LogicSystem()
{

}

void LogicSystem::Update()
{
	int size = components.size();
	for (int i = 0; i < size; i++) {
		components[i]->Update(Time::deltaTime);
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
