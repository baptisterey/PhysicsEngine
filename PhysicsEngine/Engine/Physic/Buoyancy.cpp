#include "Buoyancy.h"

#include "PhysicSystem.h"
#include "../Managers/SystemManager.h"
#include "./ForceGenerators/BuoyancySpringForce.h"

Buoyancy::Buoyancy() : ILogicComponent(), BaseComponent()
{
}

Buoyancy::Buoyancy(float maxDepth, float objectVolume, float liquidLevel, float liquidDensity) :
	BaseComponent(), ILogicComponent(), maxDepth(maxDepth), objectVolume(objectVolume), liquidLevel(liquidLevel), liquidDensity(liquidDensity)
{
}

Buoyancy::~Buoyancy()
{
}

void Buoyancy::Update(float deltaTime)
{
	PhysicSystem* physicSystem = SystemManager::GetSystemByType<PhysicSystem>();

	physicSystem->AddForce(this, new BuoyancySpringForce);
}