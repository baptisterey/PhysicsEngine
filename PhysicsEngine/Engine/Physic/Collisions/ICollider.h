#pragma once

#include "../../Base/BaseComponent.h"
#include "../PhysicSystem.h"
#include "../../Managers/SystemManager.h"

class ICollider : virtual public BaseComponent {
public:
	ICollider();
	virtual ~ICollider();

	float GetBroadRadius();
protected:
	float broadRadius = 0;
};