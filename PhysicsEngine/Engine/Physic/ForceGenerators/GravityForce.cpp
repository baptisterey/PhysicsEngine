#include "GravityForce.h"

#include "../PhysicSystem.h"

GravityForce::GravityForce() : IForceGenerator()
{
}


GravityForce::~GravityForce()
{
}

void GravityForce::UpdateForce(IPhysicComponent * physicComponent, float deltaTime)
{
	physicComponent->AddForce(Vector3(0, -PhysicSystem::GRAVITY_CONST * physicComponent->GetMass(), 0));
}
