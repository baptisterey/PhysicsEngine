#include "StiffSpringForce.h"

StiffSpringForce::StiffSpringForce() : IForceGenerator(), anchor(Vector3()), k(0), damping(NULL)
{
}

StiffSpringForce::StiffSpringForce(Vector3 anchor, float k, float damping) : IForceGenerator(), anchor(anchor), k(k), damping(damping)
{
}

StiffSpringForce::~StiffSpringForce()
{
}

void StiffSpringForce::UpdateForce(IPhysicComponent* physicComponent, float deltaTime)
{
	Vector3 pt;
	Vector3 p0 = physicComponent->GetOwner()->GetPosition();
	Vector3 velocity = physicComponent->GetVelocity();

	if (damping == 1 || damping == NULL) { // infinite oscillation
		float khi = sqrt(k / physicComponent->GetMass());
		pt = (p0 * cos(khi * deltaTime)) + (velocity / khi) * sin(khi * deltaTime);
	}
	else {
		float gamma = 1 / 2 * sqrt(4 * k - (damping * damping));
		Vector3 c = (p0 * damping / (2 * gamma)) + (physicComponent->GetVelocity() * 1 / gamma);
		pt = (p0 * cos(gamma * deltaTime) + c * sin(gamma * deltaTime)) * exp((-1 / 2) * damping * deltaTime);
	}
	physicComponent->AddForce((pt - p0) * 1 / (deltaTime * deltaTime) - velocity);
}