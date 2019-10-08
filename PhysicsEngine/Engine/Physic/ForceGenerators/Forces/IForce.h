#pragma once

#include "../../Base/IPhysicComponent.h";

class IForce
{
public:
	IForce(IPhysicComponent* physicComponent);
	virtual ~IForce();

	virtual void UpdateForce(float time) = 0;

protected:
	IPhysicComponent* physicComponent; // The physic component affected by the force.
};

