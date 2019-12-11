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

std::vector<Face> CubeCollider::GetFaces() {

	std::vector<Face> result;
	Face a, b, c, d, e, f;
	a.norm = GetOwner()->GetTransform()->GetRotation().rotatedVector(Vector3(1, 0, 0));
	a.vertices.push_back(GetOwner()->GetTransform()->LocalToWorld(Vector3(+width / 2, -height / 2, -depth / 2)));
	a.vertices.push_back(GetOwner()->GetTransform()->LocalToWorld(Vector3(+width / 2, -height / 2, +depth / 2)));
	a.vertices.push_back(GetOwner()->GetTransform()->LocalToWorld(Vector3(+width / 2, +height / 2, -depth / 2)));
	a.vertices.push_back(GetOwner()->GetTransform()->LocalToWorld(Vector3(+width / 2, +height / 2, +depth / 2)));

	b.norm = GetOwner()->GetTransform()->GetRotation().rotatedVector(Vector3(-1, 0, 0));
	b.vertices.push_back(GetOwner()->GetTransform()->LocalToWorld(Vector3(-width / 2, -height / 2, -depth / 2)));
	b.vertices.push_back(GetOwner()->GetTransform()->LocalToWorld(Vector3(-width / 2, -height / 2, +depth / 2)));
	b.vertices.push_back(GetOwner()->GetTransform()->LocalToWorld(Vector3(-width / 2, +height / 2, -depth / 2)));
	b.vertices.push_back(GetOwner()->GetTransform()->LocalToWorld(Vector3(-width / 2, +height / 2, +depth / 2)));

	c.norm = GetOwner()->GetTransform()->GetRotation().rotatedVector(Vector3(0, 1, 0));
	c.vertices.push_back(GetOwner()->GetTransform()->LocalToWorld(Vector3(-width / 2, +height / 2, -depth / 2)));
	c.vertices.push_back(GetOwner()->GetTransform()->LocalToWorld(Vector3(-width / 2, +height / 2, +depth / 2)));
	c.vertices.push_back(GetOwner()->GetTransform()->LocalToWorld(Vector3(+width / 2, +height / 2, -depth / 2)));
	c.vertices.push_back(GetOwner()->GetTransform()->LocalToWorld(Vector3(+width / 2, +height / 2, +depth / 2)));

	d.norm = GetOwner()->GetTransform()->GetRotation().rotatedVector(Vector3(0, -1, 0));
	d.vertices.push_back(GetOwner()->GetTransform()->LocalToWorld(Vector3(-width / 2, -height / 2, -depth / 2)));
	d.vertices.push_back(GetOwner()->GetTransform()->LocalToWorld(Vector3(-width / 2, -height / 2, +depth / 2)));
	d.vertices.push_back(GetOwner()->GetTransform()->LocalToWorld(Vector3(+width / 2, -height / 2, -depth / 2)));
	d.vertices.push_back(GetOwner()->GetTransform()->LocalToWorld(Vector3(+width / 2, -height / 2, +depth / 2)));

	e.norm = GetOwner()->GetTransform()->GetRotation().rotatedVector(Vector3(0, 0, 1));
	e.vertices.push_back(GetOwner()->GetTransform()->LocalToWorld(Vector3(-width / 2, -height / 2, +depth / 2)));
	e.vertices.push_back(GetOwner()->GetTransform()->LocalToWorld(Vector3(-width / 2, +height / 2, +depth / 2)));
	e.vertices.push_back(GetOwner()->GetTransform()->LocalToWorld(Vector3(+width / 2, -height / 2, +depth / 2)));
	e.vertices.push_back(GetOwner()->GetTransform()->LocalToWorld(Vector3(+width / 2, +height / 2, +depth / 2)));

	f.norm = GetOwner()->GetTransform()->GetRotation().rotatedVector(Vector3(0, 0, -1));
	f.vertices.push_back(GetOwner()->GetTransform()->LocalToWorld(Vector3(-width / 2, -height / 2, -depth / 2)));
	f.vertices.push_back(GetOwner()->GetTransform()->LocalToWorld(Vector3(-width / 2, +height / 2, -depth / 2)));
	f.vertices.push_back(GetOwner()->GetTransform()->LocalToWorld(Vector3(+width / 2, -height / 2, -depth / 2)));
	f.vertices.push_back(GetOwner()->GetTransform()->LocalToWorld(Vector3(+width / 2, +height / 2, -depth / 2)));


	result.push_back(a);
	result.push_back(b);
	result.push_back(c);
	result.push_back(d);
	result.push_back(e);
	result.push_back(f);

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
				//std::cout << "Collision Detected" << std::endl;
				
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
