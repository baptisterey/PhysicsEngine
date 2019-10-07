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

	IPhysicComponent* connectedComponent = nullptr; // The Physic Component the spring is attached to

	Vector3 connectedAnchor; // The anchor in World space the spring is attached to
	
	float k; // A coefficent for the spring force

	float initDistance; // The distance on wich the spring is at rest

	bool isSpringBungee = false; // Is the spring using bungee force ?

	void Update(float deltaTime);
};

