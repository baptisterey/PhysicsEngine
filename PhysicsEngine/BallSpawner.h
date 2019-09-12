#pragma once
#include "Engine/Base/BaseComponent.h"
#include "Engine/Logic/ILogicComponent.h"

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

	SDL_Texture* ultraballTexture = nullptr;
	SDL_Texture* superballTexture = nullptr;
	SDL_Texture* pokeballTexture = nullptr;
};

