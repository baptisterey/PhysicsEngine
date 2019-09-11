#include "RendererSystem.h"

RendererSystem::RendererSystem() : ISystem()
{

}

RendererSystem::~RendererSystem()
{
	close();
}

void RendererSystem::Update()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	for (IRendererComponent* component : components) {
		component->Render(renderer);
	}

	SDL_RenderPresent(renderer);
}

void RendererSystem::AddRendererComponent(IRendererComponent * component)
{
	if (component != nullptr) {
		components.push_back(component);
	}
}

void RendererSystem::RemoveRendererComponent(IRendererComponent * component)
{
	components.erase(std::remove(components.begin(), components.end(), component), components.end());
}

bool RendererSystem::InitRenderer(const char * title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	bool success = true;

	int flags = 0;
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}

	window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
	if (window == nullptr) {
		printf("Can't Init SDL Window !");
		success = false;
	}

	renderer = SDL_CreateRenderer(window, -1, 0);
	if (renderer == nullptr) {
		printf("Can't Init SDL Renderer !");
		success = false;
	}

	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		success = false;
	}

	return success;
}

SDL_Renderer * RendererSystem::GetRenderer()
{
	return renderer;
}

void RendererSystem::close()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	IMG_Quit();
}