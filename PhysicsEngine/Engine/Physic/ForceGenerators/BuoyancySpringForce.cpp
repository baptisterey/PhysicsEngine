#include "BuoyancySpringForce.h"

BuoyancySpringForce::BuoyancySpringForce()
{
}

BuoyancySpringForce::BuoyancySpringForce(float maxDepth, float objectVolume, float liquidLevel, float liquidDensity)
	: maxDepth(maxDepth), objectVolume(objectVolume), liquidLevel(liquidLevel), liquidDensity(liquidDensity)
{
}

BuoyancySpringForce::~BuoyancySpringForce()
{
}

void BuoyancySpringForce::UpdateForce(IPhysicComponent* physicComponent, float deltaTime)
{
	//Compute d, used to determine how the object interacts with the liquid
	d = (physicComponent->GetOwner()->GetPosition().y - liquidLevel - maxDepth) / (2 * maxDepth);

	if (d >= 1) { //Submerged entity
		physicComponent->AddForce(Vector3(0, objectVolume * liquidDensity, 0);
	}
	else if (d >= 0) { //Partially submerded entity
		physicComponent->AddForce(Vector3(0, objectVolume * liquidDensity * d, 0);
	}
	//else : object out of water, no force applied from the spring
}