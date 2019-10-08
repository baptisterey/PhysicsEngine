#include "Spring.h"

#include "./ForceGenerators/SpringForce.h"
#include "./ForceGenerators/BungeeSpringForce.h"

#include "PhysicSystem.h"
#include "../Managers/SystemManager.h"

Spring::Spring() : BaseComponent(), ILogicComponent()
{

}

Spring::Spring(float k, float initDistance) : k(k), initDistance(initDistance), BaseComponent(), ILogicComponent()
{

}

Spring::Spring(float k, float initDistance, Vector3 connectedAnchor) : k(k), initDistance(initDistance), connectedAnchor(connectedAnchor), BaseComponent(), ILogicComponent()
{

}

Spring::Spring(float k, float initDistance, IPhysicComponent* connectedComponent) : k(k), initDistance(initDistance), connectedComponent(connectedComponent), BaseComponent(), ILogicComponent()
{

}


Spring::~Spring()
{

}

void Spring::SetIsSpringBungee(bool value)
{
	isSpringBungee = value;
}

bool Spring::IsSpringBungee()
{
	return isSpringBungee;
}

void Spring::Update(float deltaTime)
{
	IPhysicComponent* physicComponent = GetOwner()->GetComponentByType<IPhysicComponent>();
	PhysicSystem* physicSystem = SystemManager::GetSystemByType<PhysicSystem>();

	if (physicSystem != nullptr && physicComponent != nullptr) {
		
		if (connectedComponent != nullptr) {

			if (isSpringBungee) {
				physicSystem->AddForce(physicComponent, new BungeeSpringForce(k, initDistance, connectedComponent->GetOwner()));
				physicSystem->AddForce(connectedComponent, new BungeeSpringForce(k, initDistance, physicComponent->GetOwner()));
			}
			else {
				physicSystem->AddForce(physicComponent, new SpringForce(k, initDistance, connectedComponent->GetOwner()));
				physicSystem->AddForce(connectedComponent, new SpringForce(k, initDistance, physicComponent->GetOwner()));
			}

		}
		else {
			if (isSpringBungee) {
				physicSystem->AddForce(physicComponent, new BungeeSpringForce(k, initDistance, connectedAnchor));
			}
			else {
				physicSystem->AddForce(physicComponent, new SpringForce(k, initDistance, connectedAnchor));
			}
			
		}
	}
}