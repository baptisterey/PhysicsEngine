#pragma once
#include "../../Math/Vector3.h"
#include "../../Base/BaseComponent.h"

class IPhysicComponent : virtual public BaseComponent
{
public:
	IPhysicComponent();
	virtual ~IPhysicComponent();

	void SetMass(float mass);
	float GetMass();
	float GetInvertedMass();

	virtual void UpdatePhysics(float deltaTime) {};

	void AddForce(const Vector3& value);
	void AddTorque(const&);
	void ClearAccumForce();

	Vector3 GetVelocity();
	Vector3 GetAcceleration();

	void SetVelocity(Vector3 value);

protected:
	Vector3 velocity, accumForce, acceleration;

private:
	float mass, invertedMass;
};
