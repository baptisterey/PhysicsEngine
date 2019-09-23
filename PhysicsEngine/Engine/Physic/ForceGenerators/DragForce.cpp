#include "DragForce.h"
#include <math.h>
#include <iostream>

DragForce::DragForce() : k1(0), k2(0)
{

}

DragForce::DragForce(float k1, float k2) : k1(k1), k2(k2)
{

}

DragForce::~DragForce()
{

}

void DragForce::UpdateForce(IPhysicComponent * physicComponent, float deltaTime)
{
	Vector3 absVelocity = Vector3::Abs(physicComponent->GetVelocity());
	Vector3 drag = (Vector3::Normalized(physicComponent->GetVelocity()) * -1.0f) * (absVelocity * k1 + (absVelocity * absVelocity) * k2);

	physicComponent->AddForce(drag);
}
