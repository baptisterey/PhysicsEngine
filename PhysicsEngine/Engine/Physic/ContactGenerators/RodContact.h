#pragma once

#include "LinkContact.h"
#include "../Base/IPhysicComponent.h"
#include "../../Base/Entity.h"



class RodContact : public LinkContact
{

public:

	RodContact::RodContact(float maxLength, IPhysicComponent* component);
	RodContact::~RodContact();
	

	Contact* GetContact(float time);
};

