#pragma once
#include "BaseComponent.h"
#include "ILogicComponent.h"

#include <SDL.h>

class BallSpawner : public BaseComponent, public ILogicComponent
{
public:
	BallSpawner();
	~BallSpawner();

	void Update(float deltaTime);

private:

	void SpawnBasketBall();

	SDL_Texture* basketballTexture = nullptr;
};

