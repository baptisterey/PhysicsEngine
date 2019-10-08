#pragma once
#include "../Engine/Base/BaseComponent.h"
#include "../Engine/Logic/ILogicComponent.h"

#include "../Engine/Managers/SystemManager.h"
#include "../Engine/Managers/EntityManager.h"
#include "../Engine/Physic/Particle.h"
#include "../Engine/Renderer/TextureRenderer.h"
#include "../Engine/Utils/Time.h"
#include "../Engine/Renderer/RendererSystem.h"
#include "../Engine/Physic/ForceGenerators/Spring.h"

#include "../Engine/Managers/SystemManager.h"
#include "../Engine/EventSystem.h"

#include "../Engine/Physic/ForceGenerators/Buoyancy.h"
#include "KeyController.h"

#include "../Engine/Physic/ContactGenerators/RodContact.h"
#include "../Engine/Physic/ContactGenerators/CableContact.h"

#include <SDL.h>

class BallSpawner : public BaseComponent, public ILogicComponent
{
public:
	BallSpawner();
	~BallSpawner();

	void Update(float deltaTime);

private:

	void SpawnSuperBall();
	void SpawnPokeBall();
	void SpawnUltraBall();

	void SpawnUltraBallSpring();
	void SpawnSuperBallBuoyancy();

	void SpawnSuperBallRod();

	SDL_Texture* ultraballTexture = nullptr;
	SDL_Texture* superballTexture = nullptr;
	SDL_Texture* pokeballTexture = nullptr;
};
