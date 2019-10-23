#pragma once

#include "../Base/IPhysicComponent.h"
#include "../../Math/Vector3.h"

#include "IForceGenerator.h"

#include "./Forces/StiffSpringForce.h"

class Stiff : public IForceGenerator
{
public:
	Stiff();
	Stiff(Vector3 anchor, float k, float damping);

	~Stiff();

	std::vector<IForce*> GetForces(float time);

private:
	Vector3 anchor;
	float k; //Elasticity constant
	float damping;
};
