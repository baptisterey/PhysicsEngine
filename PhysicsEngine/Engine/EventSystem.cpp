#include "EventSystem.h"

EventSystem::EventSystem() : ISystem()
{

}


EventSystem::~EventSystem()
{
}

void EventSystem::Update()
{
	SDL_PollEvent(&event);
}
