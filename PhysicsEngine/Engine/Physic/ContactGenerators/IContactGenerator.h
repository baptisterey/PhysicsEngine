#pragma once

#include "../Contact.h"

class IContactGenerator
{
public:
	IContactGenerator();
	~IContactGenerator();

	virtual Contact* GetContact(float time) = 0;
};

