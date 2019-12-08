#pragma once

#include <vector>

#include "../../Base/BaseComponent.h"
#include "../../Managers/SystemManager.h"


struct Face {
	Vector3 norm;
	std::vector<Vector3> vertexs;
};


class ICollider : virtual public BaseComponent {
public:
	ICollider();
	virtual ~ICollider();

	virtual std::vector<Vector3> getVertexs() = 0;
	virtual std::vector<Face> getFaces() = 0;
	virtual bool related(Face f) = 0;

	float GetBroadRadius();
protected:
	float broadRadius = 0;
};