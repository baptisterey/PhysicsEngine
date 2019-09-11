#include "BallSpawner.h"

#include <SDL.h>

#include "SystemManager.h"
#include "EntityManager.h"
#include "Particle.h"
#include "TextureRenderer.h"
#include "Time.h"
#include "RendererSystem.h"

#include "SystemManager.h"
#include "EventSystem.h"

#include <iostream>

BallSpawner::BallSpawner() : BaseComponent(), ILogicComponent()
{
	Time::timeScale = 5.0f; // For the sake of the demonstration

	SDL_Renderer* renderer = SystemManager::GetSystemByType<RendererSystem>()->GetRenderer();
	basketballTexture = TextureRenderer::LoadTexture("images/basketball.png", renderer);
}


BallSpawner::~BallSpawner()
{
	if (basketballTexture != nullptr) {
		SDL_DestroyTexture(basketballTexture);
	}
}

void BallSpawner::Update(float deltaTime)
{

	SDL_Event* event = &SystemManager::GetSystemByType<EventSystem>()->event;
	switch (event->type) {
		case SDL_KEYDOWN:
			switch (event->key.keysym.sym) {
				case SDLK_a:
					SpawnBasketBall();
					break;
			}
			break;
	}
}

void BallSpawner::SpawnBasketBall()
{
	Entity* newEntity = EntityManager::CreateEntity("BasketBall", { new Particle(Vector3(350, 250, 0), Vector3(25, -30, 0)), new TextureRenderer() });
	newEntity->GetComponentByType<TextureRenderer>()->SetTexture(basketballTexture);
}



