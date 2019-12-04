#include "PlaneCollider.h"

PlaneCollider::PlaneCollider()
{
}

PlaneCollider::PlaneCollider(Vector3 normal, float offset) : normal(normal), offset(offset)
{
}

PlaneCollider::~PlaneCollider()
{
}