#pragma once
#include "ISystem.h"
#include "IRendererComponent.h"

#include <vector>
#include <algorithm>

#include <SDL.h>
#include <stdio.h>
#include <string>

#include "SDL_image.h"

class RendererSystem : public ISystem
{
public:
	RendererSystem();
	~RendererSystem();

	void Update();

	void AddRendererComponent(IRendererComponent* component);
	void RemoveRendererComponent(IRendererComponent* component);

	bool InitRenderer(const char * title, int xpos, int ypos, int width, int height, bool fullscreen);

	SDL_Renderer* GetRenderer();

private:
	std::vector<IRendererComponent*> components;

	void close();

	//Screen dimension constants
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;

	SDL_Window* window;
	SDL_Renderer* renderer;
};

