#pragma once
#include "../Base/IForceGenerator.h"
#include "../Base/IPhysicComponent.h"
#include "../../Math/Vector3.h"

class DragForce :
	public IForceGenerator
{
public:
	DragForce();
	DragForce(float k1, float k2);

	~DragForce();

	void UpdateForce(IPhysicComponent* physicComponent, float deltaTime);

private:
	float k1, k2;
};

