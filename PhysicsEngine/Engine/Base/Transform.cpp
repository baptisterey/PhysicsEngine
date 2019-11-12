#include "Transform.h"



Transform::Transform()
{
}


Transform::~Transform()
{
}

Vector3 Transform::GetPosition()
{
	return position;
}

void Transform::SetPosition(Vector3 & const value)
{
	position = value;
}

Quaternion Transform::GetRotation()
{
	return rotation;
}

void Transform::SetRotation(Quaternion & const value)
{
	rotation = value;
}

Vector3 Transform::WorldToLocal(Vector3 & const value)
{
	return value - position;
}

Vector3 Transform::LocalToWorld(Vector3 & const value)
{
	return value + position;
}
