#include "LinkContact.h"

LinkContact::LinkContact(float maxLenght, IPhysicComponent* component) : maxLenght(maxLenght), linkComponent(component)
{

}


LinkContact::~LinkContact()
{
}

float LinkContact::CurrentLenght()
{
	IPhysicComponent* mine = GetOwner()->GetComponentByType<IPhysicComponent>();
	if (mine != nullptr) {

		float distance = Vector3::Distance(mine->GetOwner()->GetTransform()->GetPosition(), linkComponent->GetOwner()->GetTransform()->GetPosition());
		distance = distance < 0 ? distance *= -1 : distance;

		return distance;
	}
	return 0;
}