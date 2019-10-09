#include "Buoyancy.h"

Buoyancy::Buoyancy() : maxDepth(0), objectVolume(1), liquidLevel(0), liquidDensity(1), IForceGenerator()
{

}

Buoyancy::Buoyancy(float maxDepth, float objectVolume, float liquidLevel, float liquidDensity) :
	maxDepth(maxDepth), objectVolume(objectVolume), liquidLevel(liquidLevel), liquidDensity(liquidDensity), IForceGenerator()
{

}

Buoyancy::~Buoyancy()
{

}

std::vector<IForce*> Buoyancy::GetForces(float time)
{
	IPhysicComponent* physicComponent = GetOwner()->GetComponentByType<IPhysicComponent>();

	return { new BuoyancySpringForce(physicComponent, maxDepth, objectVolume, liquidLevel, liquidDensity) };
}