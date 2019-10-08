#pragma once
#include "./IForce.h"
#include "../../Base/IPhysicComponent.h"

class SpringForce : public IForce
{
public:

	float k, l0; //k coefficient de raideur et l0 longueur a l'origine
	Entity* attachedEntity;
	Vector3 anchor; // ancre � laquelle est attach�e la force si aucune entit� n'est trouv�e

	SpringForce(IPhysicComponent* physicComponent);
	SpringForce(IPhysicComponent* physicComponent, float k, float l0);
	SpringForce(IPhysicComponent* physicComponent, float k, float l0, Vector3 anchor);
	SpringForce(IPhysicComponent* physicComponent, float k, float l0, Entity* attachedEntity);
	~SpringForce();

	void UpdateForce(float deltaTime);
};

