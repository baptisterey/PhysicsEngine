#pragma once

#include "../../Base/BaseComponent.h"

class ICollider : virtual public BaseComponent {
public:
	ICollider();
	virtual ~ICollider();

	float GetBroadRadius();
protected:
	float broadRadius;
};