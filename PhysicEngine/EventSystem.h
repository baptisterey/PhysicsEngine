#pragma once
#include "ISystem.h"
#include <SDL.h>
class EventSystem : public ISystem
{
public:
	EventSystem();
	~EventSystem();

	void Update();

	SDL_Event event;
};

