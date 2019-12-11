#include "ContactRigidbody.h"
#include <string>

ContactRigidbody::ContactRigidbody(IPhysicComponent * component1, IPhysicComponent * component2, Vector3 pos, float penetration, Vector3 normale) : component1(component1), component2(component2), position(pos), penetration(penetration), normale(normale)
{

}

ContactRigidbody::~ContactRigidbody()
{

}

std::string ContactRigidbody::ToString()
{
	return "Collision Detected - at point : " + position.ToString() + " - normal : " + normale.ToString() +  " - penetration : "  + std::to_string(penetration);
}
