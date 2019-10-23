#include "BuoyancySpringForce.h"

#include <iostream>

BuoyancySpringForce::BuoyancySpringForce(IPhysicComponent* physicComponent) : IForce(physicComponent), maxDepth(0), objectVolume(1), liquidLevel(0), liquidDensity(1)
{

}


BuoyancySpringForce::BuoyancySpringForce(IPhysicComponent* physicComponent, float maxDepth, float objectVolume, float liquidLevel, float liquidDensity) :
	IForce(physicComponent), maxDepth(maxDepth), objectVolume(objectVolume), liquidLevel(liquidLevel), liquidDensity(liquidDensity)
{

}

BuoyancySpringForce::~BuoyancySpringForce()
{

}

void BuoyancySpringForce::UpdateForce(float deltaTime)
{
	if (maxDepth != 0) {
		//Compute d, used to determine how the object interacts with the liquid_
		float d = (physicComponent->GetOwner()->GetPosition().y - liquidLevel - maxDepth) / (2 * maxDepth);

		if (d >= 1) { //Submerged entity
			physicComponent->AddForce(Vector3(0, (objectVolume * liquidDensity) * -1, 0));
		}
		else if (d >= 0) { //Partially submerded entity
			physicComponent->AddForce(Vector3(0, (objectVolume * liquidDensity * d) * -1, 0));
		}
		//else : object out of water, no force applied by the spring
	}
}