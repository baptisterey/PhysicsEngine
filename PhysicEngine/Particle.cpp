#include "Particle.h"
#include <math.h> 

Particle::Particle() {
	position = Vector3();
	velocity = Vector3();
	acceleration = Vector3();
}


Particle::Particle(Vector3 pos, Vector3 vel, Vector3 acc) {
	position = pos;
	velocity = vel;
	acceleration = acc;
}


Particle::~Particle(){
}


void Particle::updateAcceleration(Vector3 gravity) {
	acceleration = gravity;

}

void Particle::updateVelocity(float fTime, float damp) {
	velocity = velocity * pow(damp,fTime) + acceleration * fTime;

}

void Particle::updatePosition(float fTime, float damp) {
	position = position + velocity * fTime;

}


void Particle::updateParticle(float fTime, float damp, Vector3 gravity) {
	updatePosition(fTime, damp);
	updateVelocity(fTime, damp);
	updateAcceleration(gravity);
}