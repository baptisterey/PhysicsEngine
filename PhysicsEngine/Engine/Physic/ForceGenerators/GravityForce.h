#pragma once
#include "../Base/IForceGenerator.h"
#include "../Base/IPhysicComponent.h"

class GravityForce : public IForceGenerator
{
public:
	GravityForce();
	~GravityForce();

	void UpdateForce(IPhysicComponent* physicComponent, float deltaTime);
};

