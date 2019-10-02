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
	d = (physicComponent. - liquidLevel - maxDepth) / 2 * maxDepth;

	if (d <= 0) {
		physicComponent->AddForce()
	}
	else if (d >= 1) {

	}
	else {

	}


}
