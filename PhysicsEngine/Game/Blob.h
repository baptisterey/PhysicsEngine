#pragma once
#include "../Engine/Base/BaseComponent.h"
#include "../Engine/Logic/ILogicComponent.h"

#include "../Engine/Physic/Particle.h"
#include "../Engine/Managers/EntityManager.h"
#include "../Engine/Renderer/TextureRenderer.h"
#include "../Engine/Managers/SystemManager.h"
#include "../Engine/Renderer/RendererSystem.h"
#include "../Engine/Physic/ForceGenerators/Spring.h"
#include "../Engine/Physic/ContactGenerators/CableContact.h"

#include "../Engine/Managers/SystemManager.h"
#include "../Engine/EventSystem.h"

#include "KeyController.h"

#include <vector>
#include <SDL.h>

class Blob : public ILogicComponent
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

	float cableLength = 110.0f;

	SDL_Texture* slimeBall = nullptr;
	SDL_Texture* blobCore = nullptr;

	void Init();

	bool isComplete = true;
};
