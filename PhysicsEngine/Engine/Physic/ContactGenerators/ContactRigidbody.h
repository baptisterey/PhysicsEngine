#pragma once
#include "../../Math/Vector3.h"
#include "../Base/IPhysicComponent.h"

#include <iostream>

/// <summary>
/// Represents an contact between two physic component. Hold informations needed for the resolution of the contact.
/// </summary>
class ContactRigidbody
{
public:
	ContactRigidbody(IPhysicComponent* component1, IPhysicComponent* component2, Vector3 pos, float penetration, Vector3 normale);
	~ContactRigidbody();

	std::string ToString();


	/// <summary>
	/// The first component of the contact.
	/// </summary>
	IPhysicComponent* component1;

	/// <summary>
	/// The second component of the contact (can be nullptr)
	/// </summary>
	IPhysicComponent* component2;

	/// <summary>
	/// The position of the contact.
	/// </summary>
	Vector3 position;

	/// <summary>
	/// The penetration of the contact (how much are the objects inside each others).
	/// </summary>
	float penetration;

	/// <summary>
	/// The normale of the contact.
	/// </summary>
	Vector3 normale;
};

