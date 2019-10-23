#include "BungeeSpringForce.h"


BungeeSpringForce::BungeeSpringForce(IPhysicComponent* physicComponent) : IForce(physicComponent), k(0), l0(1), attachedEntity(NULL), anchor(Vector3())
{
}

BungeeSpringForce::BungeeSpringForce(IPhysicComponent* physicComponent, float k, float l0) : IForce(physicComponent), k(k), l0(l0), attachedEntity(NULL), anchor(Vector3())
{
}

BungeeSpringForce::BungeeSpringForce(IPhysicComponent* physicComponent, float k, float l0, Vector3 anchor) : IForce(physicComponent), k(k), l0(l0), attachedEntity(NULL), anchor(anchor)
{
}

BungeeSpringForce::BungeeSpringForce(IPhysicComponent* physicComponent, float k, float l0, Entity* attachedEntity) : IForce(physicComponent), k(k), l0(l0), attachedEntity(attachedEntity), anchor(Vector3())
{
}

BungeeSpringForce::~BungeeSpringForce()
{
}


void BungeeSpringForce::UpdateForce(float deltaTime)
{
	if (attachedEntity != NULL) //calcul avec une entit�
	{
		if (l0 - Vector3::Distance(physicComponent->GetOwner()->GetPosition(), attachedEntity->GetPosition()) <= 0)
		{
			physicComponent->AddForce(Vector3::Normalized(physicComponent->GetOwner()->GetPosition() - attachedEntity->GetPosition()) * (k * (l0 - Vector3::Distance(physicComponent->GetOwner()->GetPosition(), attachedEntity->GetPosition()))));
		}
		else 
		{
			physicComponent->AddForce(Vector3());
		}
	}
	else //calcul avec une ancre
	{
		if (l0 - Vector3::Distance(physicComponent->GetOwner()->GetPosition(), anchor) <= 0)
		{
			physicComponent->AddForce(Vector3::Normalized(physicComponent->GetOwner()->GetPosition() - anchor) * (k * (l0 - Vector3::Distance(physicComponent->GetOwner()->GetPosition(), anchor))));
		}
		else
		{
			physicComponent->AddForce(Vector3());
		}
	}
}
