#include "Contact.h"

Contact::Contact(IPhysicComponent * component1, float penetration) : penetration(penetration)
{
	components.push_back(component1);

	contactNormal = Vector3(0, 1, 0);
}

Contact::Contact(IPhysicComponent * component1, IPhysicComponent * component2, float penetration, bool inverseContactNormal) : penetration(penetration)
{
	components.push_back(component1);
	components.push_back(component2);

	contactNormal = Vector3::Normalized(component1->GetOwner()->GetTransform()->GetPosition() - component2->GetOwner()->GetTransform()->GetPosition());

	contactNormal = inverseContactNormal ? contactNormal * -1 : contactNormal;
}

float Contact::CalculateSeparatingVelocity() const
{
	Vector3 velocity = components[0]->GetVelocity();
	if (components.size() > 1) {
		velocity = velocity - components[1]->GetVelocity();
	}

	return Vector3::Dot(velocity, contactNormal);
}

void Contact::Resolve(float time)
{
	ResolveVelocity(time);
	ResolvePenetration(time);
}

void Contact::ResolveVelocity(float time)
{
	float separatingVelocity = CalculateSeparatingVelocity();

	// Calculate the separating velocity after the collision.
	float newSeparatingVelocity = separatingVelocity * -kRestitution;

	// Get the final velocity by substracting the separating velocity after collision with the separating velocity before collision
	// In order the keep the correct momentum.
	float totalVelocity = newSeparatingVelocity - separatingVelocity;

	// Find the total inverted mass of the objects
	float totalInvertedMass = 0;
	totalInvertedMass += components[0]->GetInvertedMass();
	if (components.size() > 1) {
		totalInvertedMass += components[1]->GetInvertedMass();
	}

	// Get the impulse perf "inverted mass" unit
	float impulse = totalVelocity / totalInvertedMass;
	Vector3 impulsePerInvertedMassUnit = contactNormal * impulse;

	// Set the velocity for each object in proportion to their inverted mass
	components[0]->SetVelocity(components[0]->GetVelocity() + impulsePerInvertedMassUnit * components[0]->GetInvertedMass());
	if (components.size() > 1) {
		components[1]->SetVelocity(components[1]->GetVelocity() - impulsePerInvertedMassUnit * components[1]->GetInvertedMass());
	}
}

void Contact::ResolvePenetration(float time)
{
	// Do anything only if there is a penetration
	if (penetration > 0) {

		float totalInvertedMass = 0;
		totalInvertedMass += components[0]->GetInvertedMass();

		if (components.size() > 1) {
			totalInvertedMass += components[1]->GetInvertedMass();
		}

		// Calculate the movement on total inverted mass unit
		Vector3 movementPerInvertedMass = contactNormal * (penetration / totalInvertedMass);

		// Add the impulse by proportion to the inverted mass of each objects
		components[0]->GetOwner()->GetTransform()->SetPosition(components[0]->GetOwner()->GetTransform()->GetPosition() + (movementPerInvertedMass * components[0]->GetInvertedMass()));

		if (components.size() > 1) {
			components[1]->GetOwner()->GetTransform()->SetPosition(components[1]->GetOwner()->GetTransform()->GetPosition() - (movementPerInvertedMass * components[1]->GetInvertedMass()));
		}

	}
}

void Contact::SetKRestitution(float value)
{
	kRestitution = std::max(0.0f, std::min(value, 1.0f));
}

float Contact::GetKRestitution()
{
	return kRestitution;
}
