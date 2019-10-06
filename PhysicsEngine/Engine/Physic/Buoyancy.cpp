#include "Buoyancy.h"

Buoyancy::Buoyancy() : maxDepth(0), objectVolume(1), liquidLevel(0), liquidDensity(1), BaseComponent(), ILogicComponent()

{
}

Buoyancy::Buoyancy(float maxDepth, float objectVolume, float liquidLevel, float liquidDensity) :
	maxDepth(maxDepth), objectVolume(objectVolume), liquidLevel(liquidLevel), liquidDensity(liquidDensity), BaseComponent(), ILogicComponent()
{
}

Buoyancy::~Buoyancy()
{
}

//Get the component the spring is attached to, and add the spring force to it
void Buoyancy::Update(float deltaTime)
{
	IPhysicComponent* physicComponent = GetOwner()->GetComponentByType<IPhysicComponent>();
	PhysicSystem* physicSystem = SystemManager::GetSystemByType<PhysicSystem>();

	physicSystem->AddForce(physicComponent, new BuoyancySpringForce(maxDepth, objectVolume, liquidLevel, liquidDensity));
}