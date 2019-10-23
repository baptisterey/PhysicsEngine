#include "IContactGenerator.h"
#include "../Base/IPhysicComponent.h"
#include "../../Base/Entity.h"
#include "./Contact.h"

#pragma once
class LinkContact : public IContactGenerator
{

public :

	LinkContact::LinkContact(float maxLength, IPhysicComponent* component);
	LinkContact::~LinkContact();

	float CurrentLenght();
	virtual Contact* GetContact(float time) = 0;

protected :
	IPhysicComponent* linkComponent;
	float maxLenght;
};

