#pragma once
#include "../Engine/Base/BaseComponent.h"
#include "../Engine/Logic/ILogicComponent.h"

#include "../Engine/Physic/Particle.h"
#include "../Engine/Managers/EntityManager.h"
#include "../Engine/Renderer/TextureRenderer.h"
#include "../Engine/Managers/SystemManager.h"
#include "../Engine/Renderer/RendererSystem.h"
#include "../Engine/Physic/Spring.h"

#include "KeyController.h"

#include <vector>
#include <SDL.h>

class Blob : public BaseComponent, public ILogicComponent
{
public:

	Blob();
	Blob(int nbParticles, float k);

	~Blob();

	void Update(float deltaTime);

private:

	bool isInit = false;

	Particle* core; //Center particle
	std::vector<Particle*> particles; //Surrounding particles
	int nbParticles; //Number of surrounding particles
	float k; //Spring force coefficient

	SDL_Texture* ultraballTexture = nullptr;
	SDL_Texture* superballTexture = nullptr;
	SDL_Texture* pokeballTexture = nullptr;
};
