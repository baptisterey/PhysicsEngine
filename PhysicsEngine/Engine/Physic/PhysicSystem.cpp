#include "PhysicSystem.h"

#include "Collisions/OctoTree.h"
#include "Collisions/ICollider.h"
#include "ContactGenerators/ContactRigidbody.h"

PhysicSystem::PhysicSystem() : ISystem()
{
	// We create the octotree based on the demonstration room
	float sizeOfTheRoom = 650;
	tree = new OctoTree(0, Vector3(-sizeOfTheRoom / 1.5, -sizeOfTheRoom / 2, -sizeOfTheRoom / 1.5), Vector3(sizeOfTheRoom - sizeOfTheRoom / 1.5, sizeOfTheRoom, sizeOfTheRoom - sizeOfTheRoom / 1.5));
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

	// TODO : Resolve all the contacts

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

// ------- OLD FUNCTIONS ---------------
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
// -------------------------------------

void PhysicSystem::SearchBroadCollisions(std::vector<CollidingEntities>& groups)
{
	
	tree->Clear();

	// We add every vertices in the octotree
	for (ICollider* c : colliders) {

		if (c->IsActive()) {
			std::vector<Vector3> vertices = c->GetVertices();
			for (Vector3 v : vertices) {
				tree->Insert(v, c);
			}
		}
	}
	
	// We retrive for all vertices the potential collisions via a collider
	for (ICollider* c : colliders) {
		
		std::vector<Vector3> vertexs = c->GetVertices();
		
		for (Vector3 v : vertexs) { 
			std::vector<ICollider*> collidersToTest = tree->Retrieve(v, c);
			for (auto colliderToTest : collidersToTest) {
				CollidingVertex collidingVertex = { c, v };
				groups.push_back({ collidingVertex, colliderToTest }); // Add the colliding entities for the narrow phase.
			}
		}
	}
}

void PhysicSystem::SearchNarrowCollisions(std::vector<CollidingEntities>& groups)
{
	int size = groups.size();
	for (int i = 0; i < size; i++) {

		// We test if the specific vertx collide with the collider to test
		std::vector<ContactRigidbody> contacts = groups[i].colliderToTest->ResolveCollision(groups[i].collidingVertex);
		for each (auto contact in contacts) // We have contacts
		{
			// For the demonstration we simply desactivate the rigidbody and collider of the component and move on.
			if (contact.component1->IsActive()) {

				std::cout << contact.ToString() << std::endl;
				contact.component1->SetActive(false);

				ICollider* collider = contact.component1->GetOwner()->GetComponentByType<ICollider>();
				collider->SetActive(false);
			}
		}
	}
}

