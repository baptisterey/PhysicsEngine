#pragma once

#include <vector>

#include "../../Base/BaseComponent.h"
#include "../../Managers/SystemManager.h"
#include "../ContactGenerators/ContactRigidbody.h";

#include "../PhysicSystem.h"


class ICollider : virtual public BaseComponent {
public:
	ICollider();
	virtual ~ICollider();

	virtual std::vector<Vector3> GetVertices() = 0;

	/// <summary>
	/// Try to find collision between the two colliders and returns the list of contacts as a vector of ContactRigidbody.
	/// </summary>
	/// <param name="collider">The collider to test.</param>
	/// <returns>All the collisions found for this frame.</returns>
	virtual std::vector<ContactRigidbody> ResolveCollision(ICollider* collider) = 0;

	/// <summary>
/// Try to find the collision between the collider and a vertex.
/// </summary>
/// <param name="collider">The collider to test.</param>
/// <returns>All the collisions found for this frame.</returns>
	virtual std::vector <ContactRigidbody> ResolveCollision(CollidingVertex collidingVertex) = 0;

	/// <summary>
	/// Return radius of an sphere that encapsulate all the collider.
	/// </summary>
	/// <returns>The radius of the broading sphere.</returns>
	float GetBroadRadius();
protected:
	float broadRadius = 0;
};