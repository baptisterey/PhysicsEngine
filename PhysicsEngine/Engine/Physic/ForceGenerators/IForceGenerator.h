#pragma once

#include <vector>
#include "./Forces/IForce.h";
#include "../../Base/BaseComponent.h";

class IForceGenerator : virtual public BaseComponent
{
public:

	IForceGenerator();
	virtual ~IForceGenerator();

	virtual std::vector<IForce*> GetForces(float time) = 0;
};

