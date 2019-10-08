#include "RodContact.h"


RodContact::RodContact(float maxLenght, IPhysicComponent* component1, IPhysicComponent* component2) :
	LinkContact(maxLenght, component1, component2),
{
}


Contact* CableContact::AddContact(float time)
{
	if (CurrentLenght() < maxLenght) {

		return nullptr;
	}
	else
	{
		Contact cable = Contact(linkComponents[0], linkComponents[1], CurrentLenght() - maxLenght);
		cable.SetKRestitution(0.0f);
		return &cable;
	}
}
