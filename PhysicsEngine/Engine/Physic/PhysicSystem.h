#pragma once

#include <vector>
#include <algorithm>
#include "../Utils/Time.h"

#include "../Base/ISystem.h"
#include "Base/IPhysicComponent.h"

#include "./ContactGenerators/IContactGenerator.h";
#include "./ContactGenerators/Contact.h";

#include "./ForceGenerators/IForceGenerator.h"

class PhysicSystem : public ISystem
{
public:
	PhysicSystem();
	~PhysicSystem();

	static const int GRAVITY_CONST = 10;

	virtual void Update();

	void AddPhysicComponent(IPhysicComponent* component);
	void RemovePhysicComponent(IPhysicComponent* component);

	void AddContactGenerator(IContactGenerator* contactGenerator);
	void RemoveContactGenerator(IContactGenerator* contactGenerator);

	void AddForceGenerator(IForceGenerator* forceGenerator);
	void RemoveForceGenerator(IForceGenerator* forceGenerator);

private:

	std::vector<IPhysicComponent*> components; // The physics component currently in game
	std::vector<IContactGenerator*> contactGenerators; // The components that can generate an contact
	std::vector<IForceGenerator*> forceGenerators; // The components that can generate forces

	std::vector<IForce*> forces;
	std::vector<Contact*> contacts;

	void GenerateInterprenationContacts();
	void GenerateGroundContacts();

	void ResolveContacts();
};
