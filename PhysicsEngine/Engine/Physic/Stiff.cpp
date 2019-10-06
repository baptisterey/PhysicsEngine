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

void Stiff::Update(float deltaTime)
{
	IPhysicComponent* physicComponent = GetOwner()->GetComponentByType<IPhysicComponent>();
	PhysicSystem* physicSystem = SystemManager::GetSystemByType<PhysicSystem>();

	physicSystem->AddForce(physicComponent, new StiffSpringForce(anchor, k, damping));
}