#include "./BallSpawner.h"

BallSpawner::BallSpawner() : BaseComponent(), ILogicComponent()
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
