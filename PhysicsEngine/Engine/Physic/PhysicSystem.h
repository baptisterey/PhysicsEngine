#pragma once

#include <vector>
#include <algorithm>

#include "../Base/ISystem.h"
#include "Base/IPhysicComponent.h"
#include "Base/IForceGenerator.h"

#include "../Utils/Time.h"

class PhysicSystem : public ISystem
{
public:
	PhysicSystem();
	~PhysicSystem();

	static const int GRAVITY_CONST = -10;

	virtual void Update();

	void AddPhysicComponent(IPhysicComponent* component);
	void RemovePhysicComponent(IPhysicComponent* component);

private:

	struct ForceRegister {
		IPhysicComponent* physicComponent;
		IForceGenerator* forceGenerator;

		ForceRegister(IPhysicComponent* _physicComponent, IForceGenerator* _forceGenerator) : physicComponent(_physicComponent), forceGenerator(_forceGenerator) {}

		~ForceRegister() {
			delete this->forceGenerator;
		}
	};

	std::vector<IPhysicComponent*> components;
	std::vector<ForceRegister*> forcesRegister;
};

