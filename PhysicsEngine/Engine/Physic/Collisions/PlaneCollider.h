#pragma once
#include "ICollider.h"
#include "../../Math/Vector3.h"

class PlaneCollider : public ICollider
{
public:

	PlaneCollider();
	PlaneCollider(Vector3 normal, float offset);

	~PlaneCollider();

private:

	Vector3 normal;
	float offset;
};
