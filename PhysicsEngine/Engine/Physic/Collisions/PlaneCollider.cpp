#include "PlaneCollider.h"

PlaneCollider::PlaneCollider() : ICollider()
{

}

PlaneCollider::PlaneCollider(Vector3 normal, float offset) : normal(normal), offset(offset), ICollider()
{

}

PlaneCollider::~PlaneCollider()
{

}

std::vector<Vector3> PlaneCollider::getVertexs()
{
	return std::vector<Vector3>();
}

std::vector<Face> PlaneCollider::getFaces()
{
	return std::vector<Face>();
}

bool PlaneCollider::related(Face f)
{
	return false;
}
