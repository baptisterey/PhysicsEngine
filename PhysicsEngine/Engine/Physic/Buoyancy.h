#pragma once

#include "../Base/BaseComponent.h"
#include "../Logic/ILogicComponent.h"

#include "PhysicSystem.h"
#include "../Managers/SystemManager.h"

#include "./ForceGenerators/BuoyancySpringForce.h"

class Buoyancy : public ILogicComponent, public BaseComponent {
public:

	Buoyancy();
	Buoyancy(float maxDepth, float objectVolume, float liquidLevel, float liquidDensity);
	~Buoyancy();

	void Update(float deltaTime);

private:

	float maxDepth;
	float objectVolume;
	float liquidLevel;
	float liquidDensity;
};