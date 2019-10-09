#pragma once

#include "../Engine/Logic/ILogicComponent.h"
#include "../Engine/Physic/Base/IPhysicComponent.h"
#include "../Engine/Physic/PhysicSystem.h"

#include "../Engine/Managers/SystemManager.h"
#include "../Engine/EventSystem.h"

class KeyController : public ILogicComponent
{
public:
	KeyController();
	~KeyController();

private:
	float movementSpeed = 30.0f;

	void Update(float deltaTime);
};
