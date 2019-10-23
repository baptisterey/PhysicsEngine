#include "ILogicComponent.h"

#include "../Managers/SystemManager.h"
#include "LogicSystem.h"

ILogicComponent::ILogicComponent() : BaseComponent()
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
