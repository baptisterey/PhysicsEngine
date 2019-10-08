#pragma once

#include "../Math/Vector3.h"
#include "Base/IPhysicComponent.h"
#include "../Base/BaseComponent.h"
#include "../Logic/ILogicComponent.h"

#include "./ForceGenerators/IForceGenerator.h"

class Particle : public IPhysicComponent, public IForceGenerator
{

public:

	Particle();
	Particle(Vector3 vel, float mass = 1);
	Particle(Vector3 vel, float mass, float kDrag1, float kDrag2);

	~Particle();

	std::vector<IForce*> GetForces(float time);

	void UpdatePhysics(float deltaTime);

	void SetGravity(bool gravity);
	bool IsAffectedByGravity();

private:

	float kDrag1 = 0.0f; // first coefficient used in the drag force
	float kDrag2 = 0.0f; // second coefficient used in the drag force, this one has more impact

	bool gravity = true; // Is the particle affect by the gravity ?
};
