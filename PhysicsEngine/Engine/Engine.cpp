#include "Base/ISystem.h"
#include "Base/Entity.h"
#include "Logic/LogicSystem.h"
#include "Managers/SystemManager.h"
#include "Managers/EntityManager.h"
#include "Physic/PhysicSystem.h"
#include "Physic/Particle.h"
#include "Renderer/RendererSystem.h"
#include "Renderer/ParticleRenderer.h"
#include "Utils/Time.h"

#include "EventSystem.h"
#include "../BallSpawner.h"

#include <SDL.h>
#include <gl\glew.h>
#include <SDL_opengl.h>
#include <gl\glu.h>
#include <stdio.h>
#include <string>
#include <vector>


bool InitSDL()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}

	return success;
}


int main(int argc, char* args[]) {

	if (!InitSDL()) {
		printf("Failed to initialize SDL! \n");

		return 1;
	}

	Uint64 timeNow = SDL_GetPerformanceCounter();
	Uint64 timeLast = 0;

	SystemManager::AddSystem(new EventSystem());
	SystemManager::AddSystem(new LogicSystem());
	SystemManager::AddSystem(new PhysicSystem());
	SystemManager::AddSystem(new RendererSystem());

	SystemManager::GetSystemByType<RendererSystem>()->InitRenderer("Bullet Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1020, 720, false);

	EntityManager::CreateEntity("Ball Spawner", { new BallSpawner() });

	bool running = true;
	while (running) {

		switch (SystemManager::GetSystemByType<EventSystem>()->event.type)
		{
		case SDL_QUIT:
			running = false;
			break;

		default:
			break;
		}


		for (ISystem* system : SystemManager::GetSystems()) {
			system->Update();
		}

		//handle the deltatime
		timeLast = timeNow;
		timeNow = SDL_GetPerformanceCounter();
		Time::deltaTime = (float)((timeNow - timeLast) * 1000 / (double)SDL_GetPerformanceFrequency()) * 0.001 * Time::timeScale;
	}

	//Quit SDL subsystems
	SDL_Quit();

	return 0;
}
