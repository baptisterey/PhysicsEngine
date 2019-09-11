#include <vector>
#include "ISystem.h"
#include "SystemManager.h"

#include "PhysicSystem.h"
#include "LogicSystem.h"
#include "RendererSystem.h"

#include <SDL.h>
#include <gl\glew.h>
#include <SDL_opengl.h>
#include <gl\glu.h>
#include <stdio.h>
#include <string>

#include "Time.h"

#include "EntityManager.h"
#include "Entity.h"

#include "Particle.h"
#include "TextureRenderer.h"

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


	if (InitSDL() == false) {
		printf("Failed to initialize SDL! \n");

		return 1;
	}

	Uint64 timeNow = SDL_GetPerformanceCounter();
	Uint64 timeLast = 0;

	SystemManager::AddSystem(new PhysicSystem());
	SystemManager::AddSystem(new LogicSystem());
	SystemManager::AddSystem(new RendererSystem());

	SystemManager::GetSystemByType<RendererSystem>()->InitRenderer("Bullet Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1020, 720, false);

	EntityManager::CreateEntity("Bullet", { new Particle(Vector3(250, 250, 0), Vector3(25, 10, 0)), new TextureRenderer() });

	SDL_Renderer* renderer = SystemManager::GetSystemByType<RendererSystem>()->GetRenderer();
	EntityManager::GetEntity("Bullet")->GetComponentByType<TextureRenderer>()->LoadTexture("images/basketball.png", renderer);
	
	bool running = true;
	while (running) {
		
		for (ISystem* system : SystemManager::GetSystems()) {
			system->Update();
		}

		//handle the deltatime
		timeLast = timeNow;
		timeNow = SDL_GetPerformanceCounter();
		Time::deltaTime = (float) ((timeNow - timeLast) * 1000 / (double)SDL_GetPerformanceFrequency()) * 0.001 * Time::timeScale;

		//std::cout << "FPS : " << Time::deltaTime << std::endl;
	}

	//Quit SDL subsystems
	SDL_Quit();

	return 0;
}
