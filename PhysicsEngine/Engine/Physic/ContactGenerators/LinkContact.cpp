#include "LinkContact.h"



LinkContact::LinkContact(float maxLenght, IPhysicComponent* component1, IPhysicComponent* component2) : maxLenght(maxLenght)
{

	linkComponents.push_back(component1);
	linkComponents.push_back(component2);
}

float LinkContact::CurrentLenght()
{

	return Vector3::Distance(linkComponents[0]->GetOwner()->GetPosition(), linkComponents[1]->GetOwner()->GetPosition());
}