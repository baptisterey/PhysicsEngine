#pragma once

#include "../Math/Vector3.h"
#include "Base/IPhysicComponent.h"
#include "../Base/BaseComponent.h"
#include "../Logic/ILogicComponent.h"

class Particle : public IPhysicComponent, public ILogicComponent
{

public:

	Particle();
	Particle(Vector3 vel, float mass = 1);

	~Particle();

	void Update(float deltaTime);
	void UpdatePhysics(float deltaTime);

private:

	float kDrag1 = 0.0f; // first coefficient used in the drag force
	float kDrag2 = 0.0f; // second coefficient used in the drag force, this one has more impact

	bool gravity = true; // Is the particle affect by the gravity ?
};
