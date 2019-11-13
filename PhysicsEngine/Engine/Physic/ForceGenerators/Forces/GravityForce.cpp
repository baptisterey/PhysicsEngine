#include "GravityForce.h"

GravityForce::GravityForce(IPhysicComponent* physicComponent) : IForce(physicComponent)
{

}


GravityForce::~GravityForce()
{
}

void GravityForce::UpdateForce(float deltaTime)
{
	physicComponent->AddForceAtBodyPoint(Vector3(0, -PhysicSystem::GRAVITY_CONST * physicComponent->GetMass(), 0), Vector3());
}
