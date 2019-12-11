#pragma once

#include <vector>
#include <algorithm>
#include <limits>
#include "../Utils/Time.h"

#include "../Base/ISystem.h"
#include "Base/IPhysicComponent.h"

#include "./ContactGenerators/IContactGenerator.h"
#include "./ContactGenerators/Contact.h"

#include "./ForceGenerators/IForceGenerator.h"


class CubeCollider;
class ICollider;
class OctoTree;
class Collision;
class Face;

struct CollidingEntities; 


class PhysicSystem : public ISystem
{
public:
	PhysicSystem();
	~PhysicSystem();

	static const int GROUND_POSITION = 0;
	static const int GRAVITY_CONST = 10;

	virtual void Update();

	void AddPhysicComponent(IPhysicComponent* component);
	void RemovePhysicComponent(IPhysicComponent* component);

	void AddColliderComponent(ICollider* collider);
	void RemoveColliderComponent(ICollider* collider);

	void AddContactGenerator(IContactGenerator* contactGenerator);
	void RemoveContactGenerator(IContactGenerator* contactGenerator);

	void AddForceGenerator(IForceGenerator* forceGenerator);
	void RemoveForceGenerator(IForceGenerator* forceGenerator);

	void SearchBroadCollisions(std::vector<CollidingEntities>& groups);
	void SearchNarrowCollisions(std::vector<CollidingEntities>& groups);
	void GenerateContacts(std::vector<CollidingEntities>& groups);

private:

	std::vector<IPhysicComponent*> components; // The physics component currently in game
	std::vector<ICollider*> colliders; // The colliders component currently in game
	std::vector<IContactGenerator*> contactGenerators; // The components that can generate an contact
	std::vector<IForceGenerator*> forceGenerators; // The components that can generate forces

	std::vector<IForce*> forces;
	std::vector<Contact*> contacts;
	OctoTree* tree;

	std::vector<Collision*> collisions;

	void GenerateInterprenationContacts();
	void GenerateGroundContacts();

	void ResolveContacts();
};