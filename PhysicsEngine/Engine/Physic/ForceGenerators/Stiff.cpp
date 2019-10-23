#include "Stiff.h"

Stiff::Stiff() : anchor(Vector3()), k(0), damping(NULL)
{
}

Stiff::Stiff(Vector3 anchor, float k, float damping) : anchor(anchor), k(k), damping(damping)
{
}

Stiff::~Stiff()
{
}

std::vector<IForce*> Stiff::GetForces(float time)
{
	IPhysicComponent* physicComponent = GetOwner()->GetComponentByType<IPhysicComponent>();
	return { new StiffSpringForce(physicComponent, anchor, k, damping) };
}