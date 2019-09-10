#pragma once
#include <string>
#include "Utils.h"

#include "Entity.h"

class BaseComponent
{
public:

	BaseComponent();
	~BaseComponent();

	std::string GetId();

	Entity* GetOwner();
	void SetOwner(Entity* ow);
private:

	std::string id;
	Entity* owner;
};

