#pragma once

#include "./Contact.h"
#include "../../Base/BaseComponent.h"

class IContactGenerator : virtual public BaseComponent
{
public:
	IContactGenerator();
	virtual ~IContactGenerator();

	virtual Contact* GetContact(float time) = 0;
};

