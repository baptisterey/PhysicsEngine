#include "CubeCollider.h"
#include "./PlaneCollider.h"
#include "../Base/IPhysicComponent.h"

CubeCollider::CubeCollider(float _width, float _height, float _depth) : width(_width), height(_height), depth(_depth), ICollider()
{


}

CubeCollider::~CubeCollider()
{

}

std::vector<Vector3> CubeCollider::GetVertices() {

	std::vector<Vector3> result;
	result.push_back(GetOwner()->GetTransform()->LocalToWorld(Vector3(-width / 2, -height / 2, -depth / 2)));
	result.push_back(GetOwner()->GetTransform()->LocalToWorld(Vector3(-width / 2, -height / 2, +depth / 2)));
	result.push_back(GetOwner()->GetTransform()->LocalToWorld(Vector3(-width / 2, +height / 2, -depth / 2)));
	result.push_back(GetOwner()->GetTransform()->LocalToWorld(Vector3(-width / 2, +height / 2, +depth / 2)));
	result.push_back(GetOwner()->GetTransform()->LocalToWorld(Vector3(+width / 2, -height / 2, -depth / 2)));
	result.push_back(GetOwner()->GetTransform()->LocalToWorld(Vector3(+width / 2, -height / 2, +depth / 2)));
	result.push_back(GetOwner()->GetTransform()->LocalToWorld(Vector3(+width / 2, +height / 2, -depth / 2)));
	result.push_back(GetOwner()->GetTransform()->LocalToWorld(Vector3(+width / 2, +height / 2, +depth / 2)));
	return result;
}

std::vector<ContactRigidbody> CubeCollider::ResolveCollision(ICollider * collider)
{
	if (PlaneCollider* v = dynamic_cast<PlaneCollider*>(collider)) // We test the collision with a plane collider
	{
		std::vector<ContactRigidbody> contacts;
		PlaneCollider* plane = dynamic_cast<PlaneCollider*>(collider);

		std::vector<Vector3> vertices = GetVertices();
		for (Vector3 vertex : vertices) // We test every vertices of the object
		{
			// We calculate the distance of the vertex with the plane collider, if the distance is negative, an collision occured.
			double dist = Vector3::Dot(vertex, plane->GetNormal()) + plane->GetOffset();
			if (dist < 0)
			{			
				IPhysicComponent* physicComponent = GetOwner()->GetComponentByType<IPhysicComponent>();
				if (physicComponent != nullptr && physicComponent->IsActive()) {
					contacts.push_back(ContactRigidbody(physicComponent, collider->GetOwner()->GetComponentByType<IPhysicComponent>(), vertex, dist, plane->GetNormal()));
				}
				else {
					IPhysicComponent* physicComponent2 = collider->GetOwner()->GetComponentByType<IPhysicComponent>();
					if (physicComponent2 != nullptr && physicComponent2->IsActive()) {
						contacts.push_back(ContactRigidbody(physicComponent2, nullptr, vertex, dist, plane->GetNormal()));
					}
				}
			}
		}
		return contacts;
	}
	else
	{
		//std::cout << "Can't resolve collision between those two primitives" << std::endl;
	}

	return std::vector<ContactRigidbody>();
}

std::vector<ContactRigidbody> CubeCollider::ResolveCollision(CollidingVertex collidingVertex)
{
	return std::vector<ContactRigidbody>(); // Need to implement but not needed for the demonstration
}
