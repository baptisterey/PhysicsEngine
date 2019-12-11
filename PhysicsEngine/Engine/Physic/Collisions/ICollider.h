#pragma once

#include <vector>

#include "../../Base/BaseComponent.h"
#include "../../Managers/SystemManager.h"
#include "../ContactGenerators/ContactRigidbody.h";


struct Face {
	Vector3 norm;
	std::vector<Vector3> vertices;

	bool operator== (Face const& face) {

		if (vertices.size() == face.vertices.size() && norm == face.norm) {

			for (int i = 0; i < vertices.size(); i++) {
				if (vertices[i] != face.vertices[i]) {
					return false;
				}
			}

			return true;
		}

		return false;
	}
};


class ICollider : virtual public BaseComponent {
public:
	ICollider();
	virtual ~ICollider();

	virtual std::vector<Vector3> GetVertices() = 0;
	virtual std::vector<Face> GetFaces() = 0;

	/// <summary>
	/// Try to find collision between the two colliders and returns the list of contacts as a vector of ContactRigidbody.
	/// </summary>
	/// <param name="collider">The collider to test.</param>
	/// <returns>All the collisions found for this frame.</returns>
	virtual std::vector<ContactRigidbody> ResolveCollision(ICollider* collider) = 0;

	/// <summary>
	/// Return radius of an sphere that encapsulate all the collider.
	/// </summary>
	/// <returns>The radius of the broading sphere.</returns>
	float GetBroadRadius();
protected:
	float broadRadius = 0;
};