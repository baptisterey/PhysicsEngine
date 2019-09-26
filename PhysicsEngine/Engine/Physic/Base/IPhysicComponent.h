#pragma once
#include "../../Math/Vector3.h"
#include "../../Base/BaseComponent.h"

class IPhysicComponent : public BaseComponent
{
public:
	IPhysicComponent();
	virtual ~IPhysicComponent();

	void SetMass(float mass);
	float GetMass();
	float GetInvertedMass();

	virtual void Update(float deltaTime) {};

	void AddForce(const Vector3& value);
	void ClearAccumForce();

	Vector3 GetVelocity();

protected:
	Vector3 velocity, accumForce, acceleration;

private:
	float mass, invertedMass;
};

