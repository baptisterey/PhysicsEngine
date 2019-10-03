#include "./BallSpawner.h"

#include <SDL.h>
#include <iostream>

#include "../Engine/Physic/Buoyancy.h"

BallSpawner::BallSpawner() : BaseComponent(), ILogicComponent()
{
	Time::timeScale = 5.0f; // For the sake of the demonstration

	SDL_Renderer* renderer = SystemManager::GetSystemByType<RendererSystem>()->GetRenderer();

	superballTexture = TextureRenderer::LoadTexture("../Images/superball.png", renderer);
	pokeballTexture = TextureRenderer::LoadTexture("../Images/pokeball.png", renderer);
	ultraballTexture = TextureRenderer::LoadTexture("../Images/ultra-ball.png", renderer);
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
	Entity* newEntity = EntityManager::CreateEntity("BasketBall", { new Particle(Vector3(45, -50, 0)), new TextureRenderer() });
	newEntity->SetPosition(Vector3(150, 450, 0));

	newEntity->GetComponentByType<TextureRenderer>()->SetTexture(pokeballTexture);
}

void BallSpawner::SpawnSuperBall()
{
	Entity* newEntity = EntityManager::CreateEntity("BasketBall", { new Particle(Vector3(0, -80, 0)), new TextureRenderer(), new Buoyancy(0,0,0,0) });
	newEntity->SetPosition(Vector3(150, 450, 0));

	newEntity->GetComponentByType<TextureRenderer>()->SetTexture(superballTexture);
}

void BallSpawner::SpawnUltraBall()
{
	Entity* newEntity = EntityManager::CreateEntity("BasketBall", { new Particle(Vector3(125, -18, 0)), new TextureRenderer() });
	newEntity->SetPosition(Vector3(150, 450, 0));

	newEntity->GetComponentByType<TextureRenderer>()->SetTexture(ultraballTexture);
}