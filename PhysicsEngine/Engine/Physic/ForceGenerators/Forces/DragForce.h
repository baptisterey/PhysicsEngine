#pragma once

#include "./IForce.h";
#include "../../Base/IPhysicComponent.h";
#include "../../../Math/Vector3.h";

class DragForce :
	public IForce
{
public:
	DragForce(IPhysicComponent* physicComponent);
	DragForce(IPhysicComponent* physicComponent, float k1, float k2);

	~DragForce();

	void UpdateForce(float deltaTime);

private:
	float k1, k2;
};

