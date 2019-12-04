#pragma once

#include "ICollider.h"

class CubeCollider : public ICollider {
public:
	CubeCollider(float _width, float _height, float _depth);
	~CubeCollider();

private:
	float width;
	float height;
	float depth;
};