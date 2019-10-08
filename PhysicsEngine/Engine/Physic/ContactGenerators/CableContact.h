#include "LinkContact.h"
#include "../Base/IPhysicComponent.h"
#include "../../Base/Entity.h"


#pragma once
class CableContact : public LinkContact
{

public :

	CableContact::CableContact(float maxLength, float kRestitution, IPhysicComponent* component1, IPhysicComponent* component2);


	Contact* AddContact(float time);


private :

	float kRestitution;
};

