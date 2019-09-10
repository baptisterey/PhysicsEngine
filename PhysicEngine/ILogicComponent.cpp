#include "ILogicComponent.h"

#include "SystemManager.h"
#include "LogicSystem.h"

ILogicComponent::ILogicComponent()
{
	LogicSystem* logicSystem = SystemManager::GetSystemByType<LogicSystem>();
	if (logicSystem != nullptr) {
		logicSystem->AddLogicComponent(this);
	}
}

ILogicComponent::~ILogicComponent()
{
	LogicSystem* logicSystem = SystemManager::GetSystemByType<LogicSystem>();
	if (logicSystem != nullptr) {
		logicSystem->RemoveLogicComponent(this);
	}
}
