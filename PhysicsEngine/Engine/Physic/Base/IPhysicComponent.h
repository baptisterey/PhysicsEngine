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

	void AddForceAtPoint( Vector3& const force, Vector3& const point);
	void AddForceAtBodyPoint( Vector3& const force, Vector3& const point);

	void ClearAccumForce();

	void ClearAccumTorqueForce();

	Vector3 GetVelocity();
	Vector3 GetAcceleration();

	void SetVelocity(Vector3 value);

	void ResetVelocityAndAcceleration();

protected:
	Vector3 velocity, accumForce, acceleration, accumTorque, angularVelocity, angularAcceleration;

private:
	float mass, invertedMass;
};
