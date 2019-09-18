#pragma once
#include "Engine/Base/BaseComponent.h"
#include "Engine/Logic/ILogicComponent.h"

#include <SDL.h>
#include <gl\glew.h>
#include <SDL_opengl.h>

#include "Engine/Managers/SystemManager.h"
#include "Engine/Managers/EntityManager.h"
#include "Engine/Physic/Particle.h"
#include "Engine/Renderer/ParticleRenderer.h"
#include "Engine/Utils/Time.h"
#include "Engine/Renderer/RendererSystem.h"

#include "Engine/Managers/SystemManager.h"
#include "Engine/EventSystem.h"

#include <iostream>

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

	GLuint ultraballTexture = NULL;
	GLuint superballTexture = NULL;
	GLuint pokeballTexture = NULL;
};

