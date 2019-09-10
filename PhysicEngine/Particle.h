#pragma once
#include "Vector3.h"
class Particle
{

public:

	Vector3 position, velocity, acceleration;
	

	Particle();
	Particle(Vector3 pos, Vector3 vel, Vector3 acc);
	~Particle();


	void updateAcceleration(Vector3 gravity);
	void updateVelocity(float fTime, float damp);
	void updatePosition(float fTime, float damp);
	void updateParticle(float fTime, float damp, Vector3 gravity);


};



