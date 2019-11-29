#pragma once

#include "ICollider.h"

class Collision
{
public:
	Collision(ICollider _colliderA, ICollider _colliderB);
	~Collision();
private:
	ICollider colliderA, colliderB;
};