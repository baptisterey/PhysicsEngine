#pragma once
#include "ICollider.h"
#include "../../Math/Vector3.h"

class PlaneCollider : public ICollider
{
public:

	PlaneCollider();
	PlaneCollider(Vector3 normal);

	~PlaneCollider();

	std::vector<Vector3> GetVertices();

	std::vector<ContactRigidbody> ResolveCollision(ICollider* collider);
	std::vector <ContactRigidbody> ResolveCollision(CollidingVertex collidingVertex);

	Vector3 GetNormal();
	float GetOffset();

private:

	Vector3 normal;
};
