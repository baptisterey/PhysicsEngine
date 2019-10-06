#pragma once

#include "../Base/IForceGenerator.h"

class StiffSpringForce : public IForceGenerator
{
public:
	Vector3 anchor;
	float k; //Elasticity constant
	float damping;

	StiffSpringForce();
	StiffSpringForce(Vector3 anchor, float k, float damping);

	~StiffSpringForce();

	void UpdateForce(IPhysicComponent* physicComponent, float deltaTime);
};
