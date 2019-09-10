#pragma once
#include <vector>
#include <algorithm>
#include <iostream>

#include "ILogicComponent.h"
#include "ISystem.h"

#include "Time.h"



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

