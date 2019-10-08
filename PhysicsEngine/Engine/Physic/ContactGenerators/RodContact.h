#include "LinkContact.h"
#include "../Base/IPhysicComponent.h"
#include "../../Base/Entity.h"


#pragma once
class RodContact : public LinkContact
{

public:

	RodContact::RodContact(float maxLength, IPhysicComponent* component1, IPhysicComponent* component2);


	Contact* AddContact(float time);
};

