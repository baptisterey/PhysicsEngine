#pragma once
#include "IPhysicComponent.h";

class IForceGenerator
{
public:
	
	virtual void UpdateForce(IPhysicComponent* physicComponent, float deltaTime) = 0;
};

