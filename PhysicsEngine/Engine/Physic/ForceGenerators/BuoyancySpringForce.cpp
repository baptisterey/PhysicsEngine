#include "BuoyancySpringForce.h"

BuoyancySpringForce::BuoyancySpringForce()
{
}

BuoyancySpringForce::BuoyancySpringForce(float maxDepth, float objectVolume, float liquidLevel, float liquidDensity) : maxDepth(maxDepth), objectVolume(objectVolume), liquidLevel(liquidLevel), liquidDensity(liquidDensity)
{
}



BuoyancySpringForce::~BuoyancySpringForce()
{
}

void BuoyancySpringForce::updateForce()
{
}
