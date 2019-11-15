#include "RigidbodySpawner.h"

RigidbodySpawner::RigidbodySpawner() : ILogicComponent()
{
	Time::timeScale = 5.0f; // For the sake of the demonstration

	superballTexture = ParticleRenderer::LoadTexture("Images/superball.png");
	pokeballTexture = ParticleRenderer::LoadTexture("Images/pokeball.png");
	ultraballTexture = ParticleRenderer::LoadTexture("Images/ultra-ball.png");
}


RigidbodySpawner::~RigidbodySpawner()
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

void RigidbodySpawner::Update(float deltaTime)
{
	SDL_Event* event = &SystemManager::GetSystemByType<EventSystem>()->event;
	switch (event->type) {
	case SDL_KEYDOWN:
		switch (event->key.keysym.sym) {
		case SDLK_a:
			SpawnRigidbodyTest();
			break;
		}
		break;
	}
}

void RigidbodySpawner::SpawnRigidbodyTest()
{
	Entity* newEntity = EntityManager::CreateEntity("BasketBall", { new RigidBody(1, 80, 40, 40, 1, 1), new CubeRenderer(80, 40, 40) });
	newEntity->GetTransform()->SetPosition(Vector3(150, 250, 0));

	newEntity->GetComponentByType<RigidBody>()->AddForceAtBodyPoint(Vector3(0, 0, 500), Vector3(0, 0, -10));
}