#pragma once

#include <SDL.h>

class IRendererComponent
{
public:
	IRendererComponent();
	virtual ~IRendererComponent();

	virtual void Render(SDL_Renderer* renderer) {};
};

