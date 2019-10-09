#pragma once

#include "../../Base/BaseComponent.h"

#include "./IForceGenerator.h"
#include "./Forces/BuoyancySpringForce.h"

class Buoyancy : public IForceGenerator {
public:

	Buoyancy();
	Buoyancy(float maxDepth, float objectVolume, float liquidLevel, float liquidDensity);
	~Buoyancy();

	std::vector<IForce*> GetForces(float time);

private:

	float maxDepth;
	float objectVolume;
	float liquidLevel;
	float liquidDensity;
};