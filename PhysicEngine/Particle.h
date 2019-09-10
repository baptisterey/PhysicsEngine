#pragma once

#include "Vector3.h"
#include "IPhysicComponent.h"
#include "BaseComponent.h"

class Particle : public IPhysicComponent, public BaseComponent
{

public:

	Particle();
	Particle(Vector3 pos, Vector3 vel, float mass = 1, float damping = 1);

	~Particle();

	void SetMass(float mass);
	float GetMass();
	float GetInvertedMass();

	void Update(float delta);

protected:

	float mass, invertedMass, damping;
	Vector3 position, velocity;

};
