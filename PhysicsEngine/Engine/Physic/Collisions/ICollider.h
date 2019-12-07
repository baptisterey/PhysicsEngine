#pragma once

#include "../../Base/BaseComponent.h"
#include "../../Managers/SystemManager.h"
#include "../PhysicSystem.h"


struct Face {
	Vector3 norm;
	std::vector<Vector3> vertexs;
};

class ICollider : virtual public BaseComponent {
public:
	ICollider();
	virtual ~ICollider();

	std::vector<Vector3> getVertexs();
	std::vector<Face> getFaces();
	bool related(Face f);

	float GetBroadRadius();
protected:
	float broadRadius = 0;
};