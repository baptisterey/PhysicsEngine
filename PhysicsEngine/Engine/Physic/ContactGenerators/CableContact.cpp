#include "CableContact.h"


CableContact::CableContact(float maxLenght, float kRestitution, IPhysicComponent* component1, IPhysicComponent* component2) :
	LinkContact(maxLenght, component1, component2), 
	kRestitution(kRestitution)
{
}


Contact* CableContact::AddContact(float time)
{
	if(CurrentLenght() < maxLenght) {

		return nullptr;
	}
	else
	{
		Contact cable = Contact(linkComponents[0], linkComponents[1], CurrentLenght() - maxLenght);
		cable.SetKRestitution(kRestitution);
		return &cable ;
	}
}
