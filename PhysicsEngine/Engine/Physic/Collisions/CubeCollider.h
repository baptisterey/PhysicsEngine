#pragma once

#include "ICollider.h"

class CubeCollider : public ICollider {
public:
	CubeCollider(float _width, float _height, float _depth);
	~CubeCollider();

	std::vector<Vector3> GetVertices();

	std::vector<ContactRigidbody> ResolveCollision(ICollider* collider);
	std::vector <ContactRigidbody> ResolveCollision(CollidingVertex collidingVertex);

private:
	float width;
	float height;
	float depth;
};