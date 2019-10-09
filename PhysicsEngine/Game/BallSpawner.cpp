#include "./BallSpawner.h"

#include <SDL.h>
#include <iostream>

BallSpawner::BallSpawner() : ILogicComponent()
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
		case SDLK_r:
			SpawnUltraBallSpring();
			break;
		case SDLK_q:
			SpawnSuperBallBuoyancy();
			break;
		case SDLK_d:
			SpawnSuperBallRod();
			break;
		}
		break;
	}
}

void BallSpawner::SpawnPokeBall()
{
	Entity* newEntity = EntityManager::CreateEntity("BasketBall", { new Particle(Vector3(45, -50, 0), 1 , 0.1, 0), new TextureRenderer() });
	newEntity->SetPosition(Vector3(150, 450, 0));

	newEntity->GetComponentByType<TextureRenderer>()->SetTexture(pokeballTexture);
}

void BallSpawner::SpawnSuperBall()
{
	Entity* newEntity = EntityManager::CreateEntity("BasketBall", { new Particle(Vector3(0, 0, 0), 1 , 0.1, 0), new TextureRenderer() });
	newEntity->SetPosition(Vector3(150, 450, 0));

	newEntity->GetComponentByType<TextureRenderer>()->SetTexture(superballTexture);
}

void BallSpawner::SpawnUltraBall()
{
	Entity* newEntity = EntityManager::CreateEntity("BasketBall", { new Particle(Vector3(60, -18, 0), 1 , 0.1, 0), new TextureRenderer() });
	newEntity->SetPosition(Vector3(150, 450, 0));

	newEntity->GetComponentByType<TextureRenderer>()->SetTexture(ultraballTexture);
}

void BallSpawner::SpawnUltraBallSpring()
{
	Entity* newEntity = EntityManager::CreateEntity("Anchor", { new TextureRenderer(), new KeyController(), new Particle() });
	newEntity->SetPosition(Vector3(150, 430, 0));

	newEntity->GetComponentByType<TextureRenderer>()->SetTexture(ultraballTexture);

	Entity* newEntity2 = EntityManager::CreateEntity("BasketBall", { new Particle(Vector3(10, 0, 0), 1, 0.1f, 0), new TextureRenderer(), new Spring(0.5f, 50, newEntity->GetPosition()) });
	newEntity2->SetPosition(newEntity->GetPosition());

	newEntity2->GetComponentByType<TextureRenderer>()->SetTexture(ultraballTexture);
}

void BallSpawner::SpawnSuperBallBuoyancy()
{
	Entity* newEntity = EntityManager::CreateEntity("BasketBall", { new TextureRenderer() });
	newEntity->SetPosition(Vector3(350, 400, 0));

	newEntity->GetComponentByType<TextureRenderer>()->SetTexture(superballTexture);

	newEntity = EntityManager::CreateEntity("BasketBall", { new Particle(Vector3(5, 0, 0), 1 , 0.1, 0), new TextureRenderer(), new Buoyancy(1,1,400,11) });
	newEntity->SetPosition(Vector3(350, 450, 0));

	newEntity->GetComponentByType<TextureRenderer>()->SetTexture(superballTexture);
}

void BallSpawner::SpawnSuperBallRod()
{
	Entity* newEntity = EntityManager::CreateEntity("BasketBall", { new TextureRenderer(), new Particle() });
	newEntity->SetPosition(Vector3(400, 350, 0));
	newEntity->GetComponentByType<Particle>()->SetGravity(false);

	newEntity->GetComponentByType<TextureRenderer>()->SetTexture(pokeballTexture);

	Entity* newEntity2 = EntityManager::CreateEntity("BasketBall", { new Particle(Vector3(5, 0, 0), 1 , 0.1, 0), new TextureRenderer(), new RodContact(80.0f, newEntity->GetComponentByType<Particle>()) });
	newEntity2->SetPosition(Vector3(400, 420, 0));

	newEntity2->GetComponentByType<TextureRenderer>()->SetTexture(pokeballTexture);
}