#include "IContactGenerator.h"
#include "../Base/IPhysicComponent.h"
#include "../../Base/Entity.h"
#include "../Contact.h"
#include <Vector>


#pragma once
class LinkContact : public IContactGenerator, public BaseComponent
{

public :

	LinkContact::LinkContact(float maxLength, IPhysicComponent* component1, IPhysicComponent* component2);

	float CurrentLenght();
	virtual Contact* GetContact(float time) = 0;

protected :
	std::vector<IPhysicComponent*> linkComponents;
	float maxLenght;
};

