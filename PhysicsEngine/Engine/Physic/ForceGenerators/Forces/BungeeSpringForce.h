#pragma once

#include "./IForce.h"
#include "../../Base/IPhysicComponent.h"

class BungeeSpringForce : public IForce
{
public:
	float k, l0; //k coefficient de raideur et l0 longueur a l'origine
	Entity* attachedEntity;
	Vector3 anchor;

	BungeeSpringForce(IPhysicComponent* physicComponent);
	BungeeSpringForce(IPhysicComponent* physicComponent, float k, float l0);
	BungeeSpringForce(IPhysicComponent* physicComponent, float k, float l0, Vector3 anchor);
	BungeeSpringForce(IPhysicComponent* physicComponent, float k, float l0, Entity* attachedEntity);
	~BungeeSpringForce();

	void UpdateForce(float deltaTime);
};

