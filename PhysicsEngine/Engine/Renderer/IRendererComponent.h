#pragma once

#include <SDL.h>
#include "../Base/BaseComponent.h"

class IRendererComponent : virtual public BaseComponent
{
public:
	IRendererComponent();
	virtual ~IRendererComponent();

	virtual void Render(SDL_Renderer* renderer) {};
};

