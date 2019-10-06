#pragma once

#include "../Base/BaseComponent.h"
#include "../Logic/ILogicComponent.h"

#include "PhysicSystem.h"
#include "../Managers/SystemManager.h"

#include "ForceGenerators/StiffSpringForce.h"

class Stiff : public ILogicComponent, public BaseComponent
{
public:
	Stiff();
	Stiff(Vector3 anchor, float k, float damping);

	~Stiff();

	void Update(float deltaTime);

private:
	Vector3 anchor;
	float k; //Elasticity constant
	float damping;
};
