#include "IForce.h"

IForce::IForce(IPhysicComponent * physicComponent) : physicComponent(physicComponent)
{
}

IForce::~IForce()
{
}
