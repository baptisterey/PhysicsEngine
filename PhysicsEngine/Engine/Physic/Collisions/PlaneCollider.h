#pragma once
#include "ICollider.h"
#include "../../Math/Vector3.h"

class PlaneCollider : public ICollider
{
public:

	PlaneCollider();
	PlaneCollider(Vector3 normal, float offset);

	~PlaneCollider();

	std::vector<Vector3> getVertexs();
	std::vector<Face> getFaces();
	bool related(Face f);

private:

	Vector3 normal;
	float offset;
};
