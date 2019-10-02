#pragma once
#include "../Base/IForceGenerator.h"
#include "../Base/IPhysicComponent.h"
#include "../../Base/Entity.h"

class BungeeSpringForce : public IForceGenerator
{
public:
	float k, l0; //k coefficient de raideur et l0 longueur a l'origine
	Entity* attachedEntity;
	Vector3 anchor;

	BungeeSpringForce();
	BungeeSpringForce(float k, float l0);
	BungeeSpringForce(float k, float l0, Vector3 anchor);
	BungeeSpringForce(float k, float l0, Entity* attachedEntity);
	~BungeeSpringForce();

	void UpdateForce(IPhysicComponent* physicComponent, float deltaTime);
};

