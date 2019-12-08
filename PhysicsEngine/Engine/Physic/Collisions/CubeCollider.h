#pragma once

#include "ICollider.h"

class CubeCollider : public ICollider {
public:
	CubeCollider(float _width, float _height, float _depth);
	~CubeCollider();

	std::vector<Vector3> getVertexs();
	std::vector<Face> getFaces();
	bool related(Face f);

private:
	float width;
	float height;
	float depth;
};