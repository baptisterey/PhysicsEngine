#include "PhysicSystem.h"
#include "ForceGenerators/GravityForce.h"
#include "ForceGenerators/DragForce.h"

#include <limits>
#include <algorithm> 

PhysicSystem::PhysicSystem() : ISystem()
{

}


PhysicSystem::~PhysicSystem()
{

}

void PhysicSystem::Update()
{
	// Update all forces available
	for (ForceRegister* force : forcesRegister) {
		force->forceGenerator->UpdateForce(force->physicComponent, Time::deltaTime);
	}

	// Update every physic components
	for (IPhysicComponent* component : components) {
		component->UpdatePhysics(Time::deltaTime);
	}

	// Clear all forces for this frame
	for (auto forceRegister : forcesRegister)
	{
		delete forceRegister;
	}
	forcesRegister.clear();


	// Generate the interpenetration contacts
	GenerateInterprenationContacts();


	// Resolve the contacts
	ResolveContacts();
	

	// Clear all contacts for this frame
	for (auto contact : contacts) {
		delete contact;
	}
	contacts.clear();
}

void PhysicSystem::AddPhysicComponent(IPhysicComponent * component)
{
	if (component != nullptr) {
		components.push_back(component);
	}
}

void PhysicSystem::RemovePhysicComponent(IPhysicComponent * component)
{
	components.erase(std::remove(components.begin(), components.end(), component), components.end());
}

void PhysicSystem::AddForce(IPhysicComponent * component, IForceGenerator * force)
{
	forcesRegister.push_back(new ForceRegister(component, force));
}

void PhysicSystem::GenerateInterprenationContacts()
{
	for (int i = 0; i < components.size(); i++) {
		for (int y = i + 1; y < components.size(); y++) {

			const float distance = Vector3::Distance(components[i]->GetOwner()->GetPosition(), components[y]->GetOwner()->GetPosition());

			// For now : If the distance between the two objects is less or equal to 40, then there is interpenetration
			if (distance < 40.0f) {

				float radius1 = 20;
				float radius2 = 20;

				// Calculate how much we need to move the two objects
				float penetration = (radius1 + radius2 - distance);

				Contact* newContact = new Contact(components[i], components[y], penetration);
				contacts.push_back(newContact);
			}

		}
	}
}

void PhysicSystem::ResolveContacts()
{
	int iterationsLeft = contacts.size() * 2; // We only do 2n iterations for performances purposes and to avoid infinite loop

	while (iterationsLeft > 0) {

		// Find the minimum value of separating velocity
		float minSeparatingVelocity = std::numeric_limits<float>::max();
		float minContactIndex = 0;

		for (int i = 0; i < contacts.size(); i++) {
			float removalVelocity = contacts[i]->CalculateSeparatingVelocity();
			if (removalVelocity < minSeparatingVelocity) {
				minSeparatingVelocity = removalVelocity;
				minContactIndex = i;
			}
		}

		if (minSeparatingVelocity >= 0) {
			// We do nothing if the minimum separating velocity shows that the objects are not going in the same direction
			break; 
		}

		// Finally resolve the contact
		contacts[minContactIndex]->Resolve(Time::deltaTime);

		iterationsLeft--;
	}
}


PhysicSystem::Contact::Contact(IPhysicComponent * component1, IPhysicComponent * component2, float penetration) : penetration(penetration)
{
	components.push_back(component1);
	components.push_back(component2);

	contactNormal = Vector3::Normalized(component1->GetOwner()->GetPosition() - component2->GetOwner()->GetPosition());
}

float PhysicSystem::Contact::CalculateSeparatingVelocity() const
{
	return Vector3::Dot(components[0]->GetVelocity() - components[1]->GetVelocity(), contactNormal);
}

void PhysicSystem::Contact::Resolve(float time)
{
	ResolveVelocity(time);
	ResolvePenetration(time);
}

void PhysicSystem::Contact::ResolveVelocity(float time)
{
	float separatingVelocity = CalculateSeparatingVelocity();

	// Calculate the separating velocity after the collision.
	float newSeparatingVelocity = -separatingVelocity * kRestitution;

	// Get the velocity on "total interveted mass unit"
	float totalInvertedMass = 0;
	totalInvertedMass += components[0]->GetInvertedMass();
	totalInvertedMass += components[1]->GetInvertedMass();

	float impulse = newSeparatingVelocity / totalInvertedMass;

	Vector3 impulsePerInvertedMass = contactNormal * impulse;

	// Add the impulsion for each object in proportion to their inverted mass
	components[0]->AddImpulse(impulsePerInvertedMass * components[0]->GetMass());
	components[1]->AddImpulse(impulsePerInvertedMass * components[0]->GetMass() * -1);
}

void PhysicSystem::Contact::ResolvePenetration(float time)
{
	// Do anything only if there is a penetration
	if (penetration > 0) {

		float totalInvertedMass = 0;
		totalInvertedMass += components[0]->GetInvertedMass();
		totalInvertedMass += components[1]->GetInvertedMass();

		// Calculate the movement on total inverted mass unit
		Vector3 movementPerInvertedMass = contactNormal * (penetration / totalInvertedMass);

		// Set the position by proportion to the inverted mass of each objects
		components[0]->GetOwner()->SetPosition(components[0]->GetOwner()->GetPosition() + (movementPerInvertedMass * components[0]->GetInvertedMass()));
		components[1]->GetOwner()->SetPosition(components[1]->GetOwner()->GetPosition() - (movementPerInvertedMass * components[1]->GetInvertedMass()));
	}
}

void PhysicSystem::Contact::SetKRestitution(float value)
{
	kRestitution = std::max(0.0f, std::min(value, 1.0f));
}

float PhysicSystem::Contact::GetKRestitution()
{
	return kRestitution;
}
