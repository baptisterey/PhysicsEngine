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
