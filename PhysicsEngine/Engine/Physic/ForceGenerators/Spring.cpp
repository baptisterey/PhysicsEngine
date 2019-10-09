#include "Spring.h"

#include "./Forces/SpringForce.h"
#include "./Forces/BungeeSpringForce.h"



Spring::Spring() : IForceGenerator()
{

}

Spring::Spring(float k, float initDistance) : k(k), initDistance(initDistance), IForceGenerator()
{

}

Spring::Spring(float k, float initDistance, Vector3 connectedAnchor) : k(k), initDistance(initDistance), connectedAnchor(connectedAnchor), IForceGenerator()
{

}

Spring::Spring(float k, float initDistance, IPhysicComponent* connectedComponent) : k(k), initDistance(initDistance), connectedComponent(connectedComponent), IForceGenerator()
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

std::vector<IForce*> Spring::GetForces(float time)
{
	std::vector<IForce*> forces = std::vector<IForce*>();
	IPhysicComponent* physicComponent = GetOwner()->GetComponentByType<IPhysicComponent>();

	if (physicComponent != nullptr) {

		if (connectedComponent != nullptr) {

			if (isSpringBungee) {

				forces.push_back(new BungeeSpringForce(physicComponent, k, initDistance, connectedComponent->GetOwner()));
				forces.push_back(new BungeeSpringForce(connectedComponent, k, initDistance, physicComponent->GetOwner()));
			}
			else {
				forces.push_back(new SpringForce(physicComponent, k, initDistance, connectedComponent->GetOwner()));
				forces.push_back(new SpringForce(connectedComponent, k, initDistance, connectedComponent->GetOwner()));
			}

		}
		else {
			if (isSpringBungee) {
				forces.push_back(new BungeeSpringForce(physicComponent, k, initDistance, connectedAnchor));
			}
			else {
				forces.push_back(new SpringForce(physicComponent, k, initDistance, connectedAnchor));
			}

		}
	}

	return forces;
}