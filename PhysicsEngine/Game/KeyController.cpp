#include "KeyController.h"

KeyController::KeyController() : ILogicComponent(), BaseComponent()
{

}

KeyController::~KeyController()
{

}

void KeyController::Update(float deltaTime)
{
	Vector3 direction;
	SDL_Event* event = &SystemManager::GetSystemByType<EventSystem>()->event;
	switch (event->type) {
	case SDL_KEYDOWN:
		switch (event->key.keysym.sym) {
			case SDLK_RIGHT:
				direction = Vector3(1, 0, 0);
				break;
			case SDLK_LEFT:
				direction = Vector3(-1, 0, 0);
				break;
			case SDLK_UP:
				direction = Vector3(0, 1, 0);
				break;
			case SDLK_DOWN:
				direction = Vector3(0, -1, 0);
				break;
		}
		break;
	}

	GetOwner()->SetPosition(GetOwner()->GetPosition() + (direction * movementSpeed * deltaTime));
}
