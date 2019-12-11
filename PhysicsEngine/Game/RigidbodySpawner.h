#pragma once
#include "../Engine/Base/BaseComponent.h"
#include "../Engine/Logic/ILogicComponent.h"

#include "../Engine/Managers/EntityManager.h"
#include "../Engine/Managers/SystemManager.h"
#include "../Engine/Physic/ForceGenerators/Spring.h"
#include "../Engine/Physic/RigidBody.h"
#include "../Engine/Renderer/CubeRenderer.h"
#include "../Engine/Physic/Collisions/CubeCollider.h"
#include "../Engine/Renderer/ParticleRenderer.h"
#include "../Engine/Renderer/RendererSystem.h"
#include "../Engine/Utils/Time.h"

#include "../Engine/EventSystem.h"
#include "../Engine/Managers/SystemManager.h"

#include "../Engine/Physic/ForceGenerators/Buoyancy.h"
#include "KeyController.h"

#include "../Engine/Physic/ContactGenerators/CableContact.h"
#include "../Engine/Physic/ContactGenerators/RodContact.h"

#include <SDL.h>
#include <iostream>

class RigidbodySpawner : public ILogicComponent
{
public:
	RigidbodySpawner();
	~RigidbodySpawner();

	void Update(float deltaTime);

private:

	void SpawnRigidbodyTest();
	void SpawnRigidbodyTest2();
	void SpawnRigidbodyTest3();

};

