#pragma once
#include "../Base/IForceGenerator.h"
#include "../Base/IPhysicComponent.h"
#include "../../Math/Vector3.h"

class BuoyancySpringForce : public IForceGenerator
{
public:
	float maxDepth;
	float objectVolume;
	float liquidLevel;
	float liquidDensity;

	BuoyancySpringForce();
	BuoyancySpringForce(float maxDepth, float objectVolume, float liquidLevel, float liquidDensity);

	~BuoyancySpringForce();

	void updateForce();

}