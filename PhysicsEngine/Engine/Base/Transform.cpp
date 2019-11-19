#include "Transform.h"



Transform::Transform()
{
	transformMatrix = Quaternion::ToMatrix3(rotation).matrix3Inverse();
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
	transformMatrix = Quaternion::ToMatrix3(rotation).matrix3Inverse();
}

Vector3 Transform::WorldToLocal(Vector3 & const value)
{
	return transformMatrix.matrix3Inverse() * (value - GetPosition());
}

Vector3 Transform::LocalToWorld(Vector3 & const value)
{
	return transformMatrix * value + GetPosition();
}

Matrix3 Transform::GetTransformMatrix()
{
	return transformMatrix;
}
