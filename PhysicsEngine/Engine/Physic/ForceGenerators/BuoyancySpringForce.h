#pragma once
#include "../Base/IForceGenerator.h"
#include "../Base/IPhysicComponent.h"
#include "../../Math/Vector3.h"
#include "../../Base/Entity.h"

class BuoyancySpringForce : public IForceGenerator
{
public:

	BuoyancySpringForce();
	BuoyancySpringForce(float maxDepth, float objectVolume, float liquidLevel, float liquidDensity);

	~BuoyancySpringForce();

	void UpdateForce(IPhysicComponent* physicComponent, float deltaTime);

private:
	float maxDepth;
	float objectVolume;
	float liquidLevel;
	float liquidDensity;
}