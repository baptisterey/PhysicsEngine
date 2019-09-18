#pragma once

#include "../Math/Vector3.h"
#include "Base/IPhysicComponent.h"
#include "../Base/BaseComponent.h"

class Particle : public IPhysicComponent, public BaseComponent
{

public:

	Particle();
	Particle(Vector3 vel, float mass = 1);

	~Particle();

	void Update(float delta);


};
