#pragma once

#include "../Base/BaseComponent.h"
#include "../Logic/ILogicComponent.h"

#include "Base/IPhysicComponent.h"

#include "../Math/Vector3.h"

class Spring : public BaseComponent, public ILogicComponent
{
public:
	Spring();
	Spring(float k, float initDistance);
	Spring(float k, float initDistance, Vector3 connectedAnchor);
	Spring(float k, float initDistance, IPhysicComponent* connectedComponent);

	~Spring();

	void SetIsSpringBungee(bool value);
	bool IsSpringBungee();

private:

	IPhysicComponent* connectedComponent = nullptr;

	Vector3 connectedAnchor;
	
	float k, initDistance;

	void Update(float deltaTime);

	bool isSpringBungee = false;
};

