#pragma once
#include "../../Base/IPhysicComponent.h"
#include "../../../Math/Vector3.h"
#include "./IForce.h";

class BuoyancySpringForce : public IForce
{
public:

	BuoyancySpringForce(IPhysicComponent* physicComponent);
	BuoyancySpringForce(IPhysicComponent* physicComponent, float maxDepth, float objectVolume, float liquidLevel, float liquidDensity);

	~BuoyancySpringForce();

	void UpdateForce(float time);

private:
	float maxDepth;
	float objectVolume;
	float liquidLevel;
	float liquidDensity;
};