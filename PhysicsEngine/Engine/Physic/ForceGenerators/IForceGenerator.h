#pragma once

#include <vector>
#include "./Forces/IForce.h"

class IForceGenerator
{
public:

	IForceGenerator();
	virtual ~IForceGenerator();

	virtual std::vector<IForce*> GetForces(float time) = 0;
};

