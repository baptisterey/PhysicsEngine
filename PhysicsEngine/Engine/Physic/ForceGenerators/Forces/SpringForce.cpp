#include "SpringForce.h"

SpringForce::SpringForce(IPhysicComponent* physicComponent) : k(0), l0(1), attachedEntity(NULL), anchor(Vector3()), IForce(physicComponent)
{

}

SpringForce::SpringForce(IPhysicComponent* physicComponent, float k, float l0) : k(k), l0(l0), attachedEntity(NULL), anchor(Vector3()), IForce(physicComponent)
{

}

SpringForce::SpringForce(IPhysicComponent* physicComponent, float k, float l0, Vector3 anchor) : k(k), l0(l0), attachedEntity(NULL), anchor(anchor), IForce(physicComponent)
{

}

SpringForce::SpringForce(IPhysicComponent* physicComponent, float k, float l0, Entity* attachedEntity) : k(k), l0(l0), attachedEntity(attachedEntity), anchor(Vector3()), IForce(physicComponent)
{

}
SpringForce::~SpringForce()
{

}


void SpringForce::UpdateForce(float deltaTime)
{
	if (attachedEntity != NULL) // calcul avec une entité
	{
		physicComponent->AddForce(Vector3::Normalized(physicComponent->GetOwner()->GetPosition() - attachedEntity->GetPosition()) * (k * (l0 - Vector3::Distance(physicComponent->GetOwner()->GetPosition(), attachedEntity->GetPosition()))));
	}
	else // calcul avec une ancre 
	{
		physicComponent->AddForce(Vector3::Normalized(physicComponent->GetOwner()->GetPosition() - anchor) * (k * (l0 - Vector3::Distance(physicComponent->GetOwner()->GetPosition(), anchor))));
	}
}
