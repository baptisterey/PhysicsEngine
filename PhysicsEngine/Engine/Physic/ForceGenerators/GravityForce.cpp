#include "GravityForce.h"

#include "../PhysicSystem.h"

GravityForce::GravityForce()
{
}


GravityForce::~GravityForce()
{
}

void GravityForce::UpdateForce(IPhysicComponent * physicComponent, float deltaTime)
{
	physicComponent->AddForce(Vector3(0, -PhysicSystem::GRAVITY_CONST, 0));
}
