#include "./BallSpawner.h"
#include <SDL.h>
#include <iostream>

BallSpawner::BallSpawner() : ILogicComponent()
{
	Time::timeScale = 5.0f; // For the sake of the demonstration

	superballTexture = ParticleRenderer::LoadTexture("Images/superball.png");
	pokeballTexture = ParticleRenderer::LoadTexture("Images/pokeball.png");
	ultraballTexture = ParticleRenderer::LoadTexture("Images/ultra-ball.png");
}

BallSpawner::~BallSpawner()
{
	if (superballTexture != NULL) {
		glDeleteTextures(1, &superballTexture);
	}

	if (pokeballTexture != NULL) {
		glDeleteTextures(1, &pokeballTexture);
	}

	if (ultraballTexture != NULL) {
		glDeleteTextures(1, &ultraballTexture);
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
	Entity* newEntity = EntityManager::CreateEntity("BasketBall", { new Particle(Vector3(45, 50, 0)), new ParticleRenderer() });
	newEntity->SetPosition(Vector3(150, 250, 0));
	newEntity->GetComponentByType<ParticleRenderer>()->SetTexture(pokeballTexture);
}

void BallSpawner::SpawnSuperBall()
{
	Entity* newEntity = EntityManager::CreateEntity("SuperBall", { new Particle(Vector3(0, 80, 0)), new ParticleRenderer() });
	newEntity->SetPosition(Vector3(150, 250, 0));
	newEntity->GetComponentByType<ParticleRenderer>()->SetTexture(superballTexture);
}

void BallSpawner::SpawnUltraBall()
{
	Entity* newEntity = EntityManager::CreateEntity("UltraBall", { new Particle(Vector3(125, 18, 0)), new ParticleRenderer() });
	newEntity->SetPosition(Vector3(150, 250, 0));
	newEntity->GetComponentByType<ParticleRenderer>()->SetTexture(ultraballTexture);
}

void BallSpawner::SpawnUltraBallSpring()
{
	Entity* newEntity = EntityManager::CreateEntity("Anchor", { new ParticleRenderer(), new KeyController(), new Particle() });
	newEntity->SetPosition(Vector3(150, 270, 0));

	newEntity->GetComponentByType<ParticleRenderer>()->SetTexture(ultraballTexture);

	Entity* newEntity2 = EntityManager::CreateEntity("BasketBall", { new Particle(Vector3(10, 0, 0), 1, 0.1f, 0), new ParticleRenderer(), new Spring(0.5f, 50, newEntity->GetPosition()) });
	newEntity2->SetPosition(newEntity->GetPosition());

	newEntity2->GetComponentByType<ParticleRenderer>()->SetTexture(ultraballTexture);
}

void BallSpawner::SpawnSuperBallBuoyancy()
{
	Entity* newEntity = EntityManager::CreateEntity("BasketBall", { new ParticleRenderer() });
	newEntity->SetPosition(Vector3(350, 300, 0));

	newEntity->GetComponentByType<ParticleRenderer>()->SetTexture(superballTexture);

	newEntity = EntityManager::CreateEntity("BasketBall", { new Particle(Vector3(5, 0, 0), 1 , 0.1, 0), new ParticleRenderer(), new Buoyancy(1,1,400,11) });
	newEntity->SetPosition(Vector3(350, 250, 0));

	newEntity->GetComponentByType<ParticleRenderer>()->SetTexture(superballTexture);
}

void BallSpawner::SpawnSuperBallRod()
{
	Entity* newEntity = EntityManager::CreateEntity("BasketBall", { new ParticleRenderer(), new Particle() });
	newEntity->SetPosition(Vector3(400, 350, 0));
	newEntity->GetComponentByType<Particle>()->SetGravity(false);

	newEntity->GetComponentByType<ParticleRenderer>()->SetTexture(pokeballTexture);

	Entity* newEntity2 = EntityManager::CreateEntity("BasketBall", { new Particle(Vector3(5, 0, 0), 1 , 0.1, 0), new ParticleRenderer(), new RodContact(80.0f, newEntity->GetComponentByType<Particle>()) });
	newEntity2->SetPosition(Vector3(400, 280, 0));

	newEntity2->GetComponentByType<ParticleRenderer>()->SetTexture(pokeballTexture);
}