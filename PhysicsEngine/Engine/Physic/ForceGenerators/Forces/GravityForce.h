#pragma once
#include "./IForce.h"
#include "../../Base/IPhysicComponent.h"

#include "../../PhysicSystem.h"

class GravityForce : public IForce
{
public:
	GravityForce(IPhysicComponent* physicComponent);
	~GravityForce();

	void UpdateForce(float deltaTime);
};

