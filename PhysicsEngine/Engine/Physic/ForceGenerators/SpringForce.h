#pragma once
#include "../Base/IForceGenerator.h"
#include "../Base/IPhysicComponent.h"
#include "../../Base/Entity.h"

class SpringForce : public IForceGenerator
{
public:

	float k, l0; //k coefficient de raideur et l0 longueur a l'origine
	Entity* attachedEntity;
	Vector3 anchor; // ancre � laquelle est attach�e la force si aucune entit� n'est trouv�e

	SpringForce();
	SpringForce(float k, float l0);
	SpringForce(float k, float l0, Vector3 anchor);
	SpringForce(float k, float l0, Entity* attachedEntity);
	~SpringForce();

	void UpdateForce(IPhysicComponent* physicComponent, float deltaTime);
};

