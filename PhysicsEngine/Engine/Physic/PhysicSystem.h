#pragma once

#include <vector>
#include <algorithm>

#include "../Base/ISystem.h"
#include "Base/IPhysicComponent.h"
#include "Base/IForceGenerator.h"

#include "../Utils/Time.h"

#include "./ContactGenerators/IContactGenerator.h";

#include "Contact.h";

class PhysicSystem : public ISystem
{
public:
	PhysicSystem();
	~PhysicSystem();

	static const int GRAVITY_CONST = -10;

	virtual void Update();

	void AddPhysicComponent(IPhysicComponent* component);
	void RemovePhysicComponent(IPhysicComponent* component);

	void AddContactGenerator(IContactGenerator* contactGenerator);
	void RemoveContactGenerator(IContactGenerator* contactGenerator);

	void AddForce(IPhysicComponent* component, IForceGenerator* force);

private:

	std::vector<IPhysicComponent*> components; // All the physics component currently in game
	std::vector<IContactGenerator*> contactGenerators; // All the component that can generate an contact

	struct ForceRegister {
		IPhysicComponent* physicComponent;
		IForceGenerator* forceGenerator;

		ForceRegister(IPhysicComponent* _physicComponent, IForceGenerator* _forceGenerator) : physicComponent(_physicComponent), forceGenerator(_forceGenerator) {}

		~ForceRegister() {
			delete this->forceGenerator;
		}
	};
	std::vector<ForceRegister*> forcesRegister;

	std::vector<Contact*> contacts;

	void GenerateInterprenationContacts();
	void GenerateGroundContacts();

	void ResolveContacts();
};

