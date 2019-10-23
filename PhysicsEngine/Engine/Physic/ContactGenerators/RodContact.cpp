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

		Contact* rod = new Contact(mine, linkComponent, CurrentLenght() - maxLenght, true);
		rod->SetKRestitution(0.0f);
		return rod;
	}
	else if (CurrentLenght() < maxLenght && mine != nullptr) {
		Contact* rod = new Contact(mine, linkComponent, CurrentLenght() - maxLenght);
		rod->SetKRestitution(0.0f);
		return rod;
	}

	return nullptr;
}
