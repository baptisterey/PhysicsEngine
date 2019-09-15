#pragma once
#include <vector>
#include <algorithm>
#include <iostream>

#include "ILogicComponent.h"
#include "../Base/ISystem.h"

#include "../Utils/Time.h"



class LogicSystem : public ISystem
{

public:
	LogicSystem();
	~LogicSystem();

	virtual void Update();

	void AddLogicComponent(ILogicComponent* component);
	void RemoveLogicComponent(ILogicComponent* component);

private:
	std::vector<ILogicComponent*> components;
};

