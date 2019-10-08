#pragma once

#include "../Contact.h"

class IContactGenerator
{
public:
	IContactGenerator();
	virtual ~IContactGenerator();

	virtual Contact* GetContact(float time) = 0;
};

