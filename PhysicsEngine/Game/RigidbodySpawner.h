#pragma once
#include "../Engine/Base/BaseComponent.h"
#include "../Engine/Logic/ILogicComponent.h"

#include "../Engine/Managers/EntityManager.h"
#include "../Engine/Managers/SystemManager.h"
#include "../Engine/Physic/ForceGenerators/Spring.h"
#include "../Engine/Physic/RigidBody.h"
#include "../Engine/Renderer/CubeRenderer.h"
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
	void SpawnRigidbodyCar();
	void RigidbodyCarCrash();

private:
	void SpawnRigidbodyTest(bool force);

	GLuint ultraballTexture = NULL;
	GLuint superballTexture = NULL;
	GLuint pokeballTexture = NULL;


	Entity * Car1;
	Entity * Car2;
	bool checkCol = true;
};

