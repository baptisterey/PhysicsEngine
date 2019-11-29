#pragma once

#include "../Base/IPhysicComponent.h";
#include "../../Math/Vector3.h";

class Contact
{
public:
	Contact(IPhysicComponent* component1, float penetration);
	Contact(IPhysicComponent* component1, IPhysicComponent* component2, float penetration, bool inverseContactNormal = false);

	float CalculateSeparatingVelocity() const;

	void Resolve(float time);

	void ResolveVelocity(float time);
	void ResolvePenetration(float time);

	void SetKRestitution(float value);
	float GetKRestitution();

private:
	Vector3 contactNormal;
	Vector3 contactPoint;
	float kRestitution = 1;
	float penetration;

	std::vector<IPhysicComponent*> components;
};

