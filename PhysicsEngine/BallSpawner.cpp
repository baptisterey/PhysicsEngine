#include "BallSpawner.h"

#include <SDL.h>

#include "Engine/Managers/SystemManager.h"
#include "Engine/Managers/EntityManager.h"
#include "Engine/Physic/Particle.h"
#include "Engine/Renderer/ParticleRenderer.h"
#include "Engine/Utils/Time.h"
#include "Engine/Renderer/RendererSystem.h"

#include "Engine/Managers/SystemManager.h"
#include "Engine/EventSystem.h"

#include <iostream>

BallSpawner::BallSpawner() : BaseComponent(), ILogicComponent()
{
	Time::timeScale = 5.0f; // For the sake of the demonstration
	/*
	SDL_Renderer* renderer = SystemManager::GetSystemByType<RendererSystem>()->GetRenderer();

	superballTexture = ParticleRenderer::LoadTexture("Images/superball.png", renderer);
	pokeballTexture = ParticleRenderer::LoadTexture("Images/pokeball.png", renderer);
	ultraballTexture = ParticleRenderer::LoadTexture("Images/ultra-ball.png", renderer);
	*/
}


BallSpawner::~BallSpawner()
{
	if (superballTexture != nullptr) {
		SDL_DestroyTexture(superballTexture);
	}

	if (pokeballTexture != nullptr) {
		SDL_DestroyTexture(pokeballTexture);
	}

	if (ultraballTexture != nullptr) {
		SDL_DestroyTexture(ultraballTexture);
	}
}

void BallSpawner::Update(float deltaTime)
{
	SDL_Event* event = &SystemManager::GetSystemByType<EventSystem>()->event;
	switch (event->type) {
		case SDL_KEYDOWN:
			switch (event->key.keysym.sym) {
				case SDLK_a:
					SpawnPokeBall();
					break;
				case SDLK_z:
					SpawnSuperBall();
					break;
				case SDLK_e:
					SpawnUltraBall();
					break;
			}
			break;
	}
}

void BallSpawner::SpawnPokeBall()
{
	Entity* newEntity = EntityManager::CreateEntity("BasketBall", { new Particle(Vector3(150, 450, 0), Vector3(45, -50, 0)), new ParticleRenderer() });
	//newEntity->GetComponentByType<ParticleRenderer>()->SetTexture(pokeballTexture);
}

void BallSpawner::SpawnSuperBall()
{
	Entity* newEntity = EntityManager::CreateEntity("BasketBall", { new Particle(Vector3(150, 450, 0), Vector3(0, -80, 0)), new ParticleRenderer() });
	//newEntity->GetComponentByType<ParticleRenderer>()->SetTexture(superballTexture);
}

void BallSpawner::SpawnUltraBall()
{
	Entity* newEntity = EntityManager::CreateEntity("BasketBall", { new Particle(Vector3(150, 450, 0), Vector3(125, -18, 0)), new ParticleRenderer() });
	//newEntity->GetComponentByType<ParticleRenderer>()->SetTexture(ultraballTexture);
}
