#include "CubeCollider.h"

CubeCollider::CubeCollider(float _width, float _height, float _depth) : width(_width), height(_height), depth(_depth), ICollider()
{
	broadRadius = sqrt(pow(_width, 2) + pow(_height, 2) + pow(_depth, 2)) / 2;
}

CubeCollider::~CubeCollider()
{
}


