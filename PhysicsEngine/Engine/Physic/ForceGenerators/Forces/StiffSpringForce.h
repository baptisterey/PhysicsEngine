#pragma once

#include "IForce.h"
#include "../../Base/IPhysicComponent.h"

class StiffSpringForce : public IForce
{
public:
	Vector3 anchor;
	float k; //Elasticity constant
	float damping;

	StiffSpringForce(IPhysicComponent* physicComponent);
	StiffSpringForce(IPhysicComponent* physicComponent, Vector3 anchor, float k, float damping);

	~StiffSpringForce();

	void UpdateForce(float deltaTime);
};
