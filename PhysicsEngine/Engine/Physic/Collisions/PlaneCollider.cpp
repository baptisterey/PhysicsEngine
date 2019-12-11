#include "PlaneCollider.h"

#include "CubeCollider.h"

PlaneCollider::PlaneCollider() : ICollider()
{

}

PlaneCollider::PlaneCollider(Vector3 normal) : normal(normal), ICollider()
{

}

PlaneCollider::~PlaneCollider()
{

}

std::vector<Vector3> PlaneCollider::GetVertices()
{
	return std::vector<Vector3>();
}

std::vector<Face> PlaneCollider::GetFaces()
{
	return std::vector<Face>();
}

std::vector<ContactRigidbody> PlaneCollider::ResolveCollision(ICollider * collider)
{
	if (CubeCollider* v = dynamic_cast<CubeCollider*>(collider)) // We test the collision with a cube collider
	{
		CubeCollider* cube = dynamic_cast<CubeCollider*>(collider);

		return cube->ResolveCollision(this); // Simply call the cube's function
	}
	else
	{
		//std::cout << "Can't resolve collision between those two primitives" << std::endl;
	}

	return std::vector<ContactRigidbody>();
}

Vector3 PlaneCollider::GetNormal()
{
	return normal;
}

float PlaneCollider::GetOffset()
{
	Vector3 pos = GetOwner()->GetTransform()->GetPosition();
	return (-normal.x * pos.x) + (-normal.y * pos.y) + (-normal.z * pos.z);
}
