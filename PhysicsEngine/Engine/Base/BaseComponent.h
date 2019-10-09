#pragma once
#include <string>
#include "../Utils/Utils.h"
#include "Entity.h"

class BaseComponent
{
public:

	BaseComponent();
	virtual ~BaseComponent();

	std::string GetId();

	Entity* GetOwner();
	void SetOwner(Entity* ow);

	bool IsActive();
	void SetActive(bool value);
private:

	std::string id;
	Entity* owner;

	bool isActive = true;
};

