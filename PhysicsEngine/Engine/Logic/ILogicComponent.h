#pragma once
#include "../Base/BaseComponent.h"

class ILogicComponent : virtual public BaseComponent
{
public:

	ILogicComponent();
	virtual ~ILogicComponent();

	virtual void Update(float deltaTime) = 0;
};

