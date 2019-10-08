#pragma once

#include <vector>
#include <algorithm>

#include "../Base/ISystem.h"
#include "Base/IPhysicComponent.h"
#include "Base/IForceGenerator.h"

#include "../Utils/Time.h"

class PhysicSystem : public ISystem
{
public:
	PhysicSystem();
	~PhysicSystem();

	static const int GRAVITY_CONST = -10;

	virtual void Update();

	void AddPhysicComponent(IPhysicComponent* component);
	void RemovePhysicComponent(IPhysicComponent* component);

	void AddForce(IPhysicComponent* component, IForceGenerator* force);

private:

	std::vector<IPhysicComponent*> components;


	struct ForceRegister {
		IPhysicComponent* physicComponent;
		IForceGenerator* forceGenerator;

		ForceRegister(IPhysicComponent* _physicComponent, IForceGenerator* _forceGenerator) : physicComponent(_physicComponent), forceGenerator(_forceGenerator) {}

		~ForceRegister() {
			delete this->forceGenerator;
		}
	};
	std::vector<ForceRegister*> forcesRegister;


	struct Contact {

		Contact(IPhysicComponent* component1, float penetration);
		Contact(IPhysicComponent* component1, IPhysicComponent* component2, float penetration);

		float CalculateSeparatingVelocity() const;

		void Resolve(float time);
		
		void ResolveVelocity(float time);
		void ResolvePenetration(float time);

		void SetKRestitution(float value);
		float GetKRestitution();

	private:
		Vector3 contactNormal;

		float kRestitution = 0.5;
		float penetration;

		std::vector<IPhysicComponent*> components;
	};
	std::vector<Contact*> contacts;

	void GenerateInterprenationContacts();
	void GenerateGroundContacts();

	void ResolveContacts();
};

