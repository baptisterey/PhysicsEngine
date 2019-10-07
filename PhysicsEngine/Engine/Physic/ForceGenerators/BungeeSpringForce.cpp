#include "BungeeSpringForce.h"
#include "../PhysicSystem.h"




BungeeSpringForce::BungeeSpringForce() : k(0), l0(1), attachedEntity(NULL), anchor(Vector3())
{
}

BungeeSpringForce::BungeeSpringForce(float k, float l0) : k(k), l0(l0), attachedEntity(NULL), anchor(Vector3())
{
}

BungeeSpringForce::BungeeSpringForce(float k, float l0, Vector3 anchor) : k(k), l0(l0), attachedEntity(NULL), anchor(anchor)
{
}

BungeeSpringForce::BungeeSpringForce(float k, float l0, Entity* attachedEntity) : k(k), l0(l0), attachedEntity(attachedEntity), anchor(Vector3())
{
}

BungeeSpringForce::~BungeeSpringForce()
{
}



void BungeeSpringForce::UpdateForce(IPhysicComponent* physicComponent, float deltaTime)
{
	if (attachedEntity != NULL) //calcul avec une entité
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
