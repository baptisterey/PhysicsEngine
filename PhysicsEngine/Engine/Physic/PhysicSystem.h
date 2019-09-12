#pragma once

#include <vector>
#include <algorithm>

#include "../Base/ISystem.h"
#include "IPhysicComponent.h"

#include "../Utils/Time.h"

class PhysicSystem : public ISystem
{
public:
	PhysicSystem();
	~PhysicSystem();

	static const int GRAVITY_CONST = 10;

	virtual void Update();

	void AddPhysicComponent(IPhysicComponent* component);
	void RemovePhysicComponent(IPhysicComponent* component);

private:
	std::vector<IPhysicComponent*> components;
};

