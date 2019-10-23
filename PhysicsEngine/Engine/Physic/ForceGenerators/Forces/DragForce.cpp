#include "DragForce.h"
#include <math.h>
#include <iostream>

DragForce::DragForce(IPhysicComponent* physicComponent) : IForce(physicComponent),  k1(0), k2(0)
{

}

DragForce::DragForce(IPhysicComponent* physicComponent, float k1, float k2) : IForce(physicComponent), k1(k1), k2(k2)
{

}

DragForce::~DragForce()
{

}

void DragForce::UpdateForce(float deltaTime)
{
	Vector3 absVelocity = Vector3::Abs(physicComponent->GetVelocity());
	Vector3 drag = (Vector3::Normalized(physicComponent->GetVelocity()) * -1.0f) * (absVelocity * k1 + (absVelocity * absVelocity) * k2);

	physicComponent->AddForce(drag);
}
