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

std::vector<ContactRigidbody> PlaneCollider::ResolveCollision(CollidingVertex collidingVertex)
{
	std::vector<ContactRigidbody> contacts;

	// We calculate the distance of the vertex with the plane collider, if the distance is negative, an collision occured.
	double dist = Vector3::Dot(collidingVertex.vertex, GetNormal()) + GetOffset();
	if (dist < 0)
	{
		IPhysicComponent* physicComponent = collidingVertex.collider1->GetOwner()->GetComponentByType<IPhysicComponent>();
		if (physicComponent != nullptr && physicComponent->IsActive()) {
			contacts.push_back(ContactRigidbody(physicComponent, nullptr, collidingVertex.vertex, dist, GetNormal()));
		}
	}
	
	return contacts;

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