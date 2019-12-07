#include "PhysicSystem.h"
#include "Collisions/OctoTree.h"
#include "Collisions/CubeCollider.h"

PhysicSystem::PhysicSystem() : ISystem()
{
	float
		size = 500;

	tree = new OctoTree(0, Vector3(-11.25, -10, -1000), Vector3(1.325*size, size, 2*size));
}


PhysicSystem::~PhysicSystem()
{

}

void PhysicSystem::Update()
{
	// ----------- MANAGE FORCES -----------

	// Loop through all the force generators and add their forces
	for (IForceGenerator* forceGenerator : forceGenerators) {
		if (forceGenerator->IsActive()) {
			std::vector<IForce*> newForces = forceGenerator->GetForces(Time::deltaTime);
			forces.insert(std::end(forces), std::begin(newForces), std::end(newForces));
		}
	}

	// Update all forces available
	for (IForce* force : forces) {
		force->UpdateForce(Time::deltaTime);
	}

	// Update every physic components
	for (IPhysicComponent* component : components) {
		if (component->IsActive()) {
			component->UpdatePhysics(Time::deltaTime);
		}
	}

	// Clear all forces for this frame
	for (auto force : forces)
	{
		delete force;
	}
	forces.clear();
	// -------------------------------------


	// ---------- MANAGE COLLISIONS --------

	// Broad phase : find possible collisions
	std::vector<CollidingEntities> possibleCollisions;
	SearchBroadCollisions(possibleCollisions);

	// Narrow phase : find real collisions
	SearchNarrowCollisions(possibleCollisions);

	// Contact generation
	GenerateContacts(possibleCollisions);

	if (possibleCollisions.size())
	{

		;
	}

	// -------------------------------------


	// ---------- MANAGE CONTACTS ----------

	/*
	// Generate the interpenetration contacts
	GenerateInterprenationContacts();

	// Generate the ground contacts
	GenerateGroundContacts();

	// Loop through all the contact generators and test if they generate an contact for this frame
	for (auto contactGenerator : contactGenerators) {

		if (contactGenerator->IsActive()) {
			// Try to get an contact for this contact generator
			Contact* contact = contactGenerator->GetContact(Time::deltaTime);
			if (contact != nullptr) {
				// Add the contact only if there is one
				contacts.push_back(contact);
			}
		}
	}

	// Resolve the contacts
	ResolveContacts();

	// Clear all contacts for this frame
	for (auto contact : contacts) {
		delete contact;
	}
	contacts.clear();
	*/
	// -------------------------------------
}

void PhysicSystem::AddPhysicComponent(IPhysicComponent* component)
{
	if (component != nullptr) {
		components.push_back(component);
	}
}

void PhysicSystem::RemovePhysicComponent(IPhysicComponent* component)
{
	components.erase(std::remove(components.begin(), components.end(), component), components.end());
}

void PhysicSystem::AddColliderComponent(ICollider* collider)
{
	if (collider != nullptr) {
		colliders.push_back(collider);
	}
}

void PhysicSystem::RemoveColliderComponent(ICollider* collider)
{
	colliders.erase(std::remove(colliders.begin(), colliders.end(), collider), colliders.end());
}

void PhysicSystem::AddContactGenerator(IContactGenerator* contactGenerator)
{
	if (contactGenerator != nullptr) {
		contactGenerators.push_back(contactGenerator);
	}
}

void PhysicSystem::RemoveContactGenerator(IContactGenerator* contactGenerator)
{
	contactGenerators.erase(std::remove(contactGenerators.begin(), contactGenerators.end(), contactGenerator), contactGenerators.end());
}

void PhysicSystem::AddForceGenerator(IForceGenerator* forceGenerator)
{
	if (forceGenerator != nullptr) {
		forceGenerators.push_back(forceGenerator);
	}
}

void PhysicSystem::RemoveForceGenerator(IForceGenerator* forceGenerator)
{
	forceGenerators.erase(std::remove(forceGenerators.begin(), forceGenerators.end(), forceGenerator), forceGenerators.end());
}

void PhysicSystem::GenerateInterprenationContacts()
{
	for (int i = 0; i < components.size(); i++) {
		for (int y = i + 1; y < components.size(); y++) {

			const float distance = Vector3::Distance(components[i]->GetOwner()->GetTransform()->GetPosition(), components[y]->GetOwner()->GetTransform()->GetPosition());

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

void PhysicSystem::GenerateGroundContacts()
{
	// Temporary solution to detect collision with the ground
	for (int i = 0; i < components.size(); i++) {

		// The particle is in contact with the ground if its position is inferior to groundPosition
		if (components[i]->GetOwner()->GetTransform()->GetPosition().y < PhysicSystem::GROUND_POSITION) {

			Contact* newContact = new Contact(components[i], PhysicSystem::GROUND_POSITION - components[i]->GetOwner()->GetTransform()->GetPosition().y);
			contacts.push_back(newContact);
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

void PhysicSystem::SearchBroadCollisions(std::vector<CollidingEntities>& groups)
{
	int size = colliders.size();

	// Collider regionalization
	tree->Clear();
	for (ICollider* c : colliders) {
		std::vector<Vector3> vertexs = c->getVertexs();
		std::vector<Face> faces = c->getFaces();
		for (Vector3 v : vertexs){ tree->Insert(v); }
		for (Face f : faces){ tree->Insert(f); }

	}

	// Check broad collisions for every collider
	for (ICollider* c : colliders) {

		std::vector<Vector3> vertexs = c->getVertexs();
		//std::vector<Face> faces = c->getFaces();

	
		for (Vector3 v : vertexs) { 
			std::vector<Face> possibleCollisions;
			possibleCollisions = tree->Retrieve(v); 
			for (Face collide : possibleCollisions)
			{
				if(!(c->related(collide)))
				{
					groups.push_back({ v,collide });
				}
			}
		}
	}
}

void PhysicSystem::SearchNarrowCollisions(std::vector<CollidingEntities>& groups)
{


}

void PhysicSystem::GenerateContacts(std::vector<CollidingEntities>& groups) {

}


