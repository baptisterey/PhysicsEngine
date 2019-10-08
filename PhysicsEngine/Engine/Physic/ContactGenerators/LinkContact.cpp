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
		return Vector3::Distance(mine->GetOwner()->GetPosition(), linkComponent->GetOwner()->GetPosition());
	}
	return 0;
}