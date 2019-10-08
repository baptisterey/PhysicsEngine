#include "CableContact.h"


CableContact::CableContact(float maxLenght, float kRestitution, IPhysicComponent* component) :
	LinkContact(maxLenght, component), 
	kRestitution(kRestitution)
{
}

CableContact::~CableContact()
{
}


Contact* CableContact::GetContact(float time)
{
	IPhysicComponent* mine = GetOwner()->GetComponentByType<IPhysicComponent>();
	if (CurrentLenght() >= maxLenght && mine != nullptr) {

		Contact cable = Contact(mine, linkComponent, CurrentLenght() - maxLenght);
		cable.SetKRestitution(kRestitution);
		return &cable;
	}
	return nullptr;

}
