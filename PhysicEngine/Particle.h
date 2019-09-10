#pragma once
#include "Vector3.h"
class Particle
{
protected:
	float mass, invertedMass;

public:

	Vector3 position, velocity, acceleration;


	Particle();
	Particle(Vector3 pos, Vector3 vel, Vector3 acc, float mass);
	~Particle();

	void setMass(float mass);
        float getMass();
        float getInvertedMass();


	void updateAcceleration(Vector3 gravity);
	void updateVelocity(float fTime, float damp);
	void updatePosition(float fTime, float damp);
	void updateParticle(float fTime, float damp, Vector3 gravity);


};



