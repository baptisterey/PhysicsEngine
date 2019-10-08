#include "RodContact.h"


RodContact::RodContact(float maxLenght, IPhysicComponent* component) :
	LinkContact(maxLenght, component)
{
}

RodContact::~RodContact()
{
}

Contact* RodContact::GetContact(float time)
{

	IPhysicComponent* mine = GetOwner()->GetComponentByType<IPhysicComponent>();
	if (CurrentLenght() >= maxLenght && mine != nullptr) {

		Contact cable = Contact(mine, linkComponent, CurrentLenght() - maxLenght);
		cable.SetKRestitution(0.0f);
		return &cable;
	}

	return nullptr;
}
