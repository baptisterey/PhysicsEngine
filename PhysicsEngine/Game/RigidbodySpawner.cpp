#include "RigidbodySpawner.h"
#include "../Engine/Physic/Collisions/PlaneCollider.h"

RigidbodySpawner::RigidbodySpawner() : ILogicComponent()
{
	Time::timeScale = 5.0f; // For the sake of the demonstration

	/*
	float size = 500;

	Entity* newEntity = EntityManager::CreateEntity("Tree", { new CubeRenderer(1.325*size, size, size) });
	newEntity->GetTransform()->SetPosition(Vector3(320,240, -500));
	*/

	float sizeOfTheRoom = 650;

	// Create the walls of the room
	Entity* left = EntityManager::CreateEntity("Left", { new CubeRenderer(1, sizeOfTheRoom, sizeOfTheRoom), new PlaneCollider(Vector3(1, 0, 0)) });
	left->GetTransform()->SetPosition(Vector3(-sizeOfTheRoom / 2, sizeOfTheRoom/2, 0));

	Entity* right = EntityManager::CreateEntity("Right", { new CubeRenderer(1, sizeOfTheRoom, sizeOfTheRoom), new PlaneCollider(Vector3(-1, 0, 0)) });
	right->GetTransform()->SetPosition(Vector3(sizeOfTheRoom, sizeOfTheRoom / 2, 0));

	Entity* bottom = EntityManager::CreateEntity("Bottom", { new CubeRenderer(sizeOfTheRoom, 1, sizeOfTheRoom), new PlaneCollider(Vector3(0, 1, 0)) });
	bottom->GetTransform()->SetPosition(Vector3(0, -sizeOfTheRoom / 2, 0));
}


RigidbodySpawner::~RigidbodySpawner()
{

}

void RigidbodySpawner::Update(float deltaTime)
{
	SDL_Event* event = &SystemManager::GetSystemByType<EventSystem>()->event;
	switch (event->type) {
	case SDL_KEYDOWN:
		switch (event->key.keysym.sym) {
		case SDLK_a:
			SpawnRigidbodyTest2();
			break;
		case SDLK_z:
			SpawnRigidbodyTest();
			break;
		case SDLK_e:
			SpawnRigidbodyTest3();
		}

		break;
	}
}

void RigidbodySpawner::SpawnRigidbodyTest()
{
	Entity* newEntity = EntityManager::CreateEntity("BasketBall", { new CubeRenderer(40, 80, 40), new RigidBody(1, 80, 40, 40, 1, 0.9f), new CubeCollider(40, 80, 40) });
	newEntity->GetTransform()->SetPosition(Vector3(150, 250, 0));

	newEntity->GetComponentByType<RigidBody>()->AddForceAtBodyPoint(Vector3(500, 450, 50), Vector3(-8, 8,6 ));
}

void RigidbodySpawner::SpawnRigidbodyTest2()
{
	Entity* newEntity = EntityManager::CreateEntity("BasketBall", { new CubeRenderer(40, 80, 40), new RigidBody(1, 80, 40, 40, 1, 0.9f), new CubeCollider(40, 80, 40) });
	newEntity->GetTransform()->SetPosition(Vector3(150, 250, 0));

	newEntity->GetComponentByType<RigidBody>()->AddForceAtBodyPoint(Vector3(-500, 450, 50), Vector3(-8, 8, 6));
}

void RigidbodySpawner::SpawnRigidbodyTest3()
{
	Entity* newEntity = EntityManager::CreateEntity("BasketBall", { new CubeRenderer(40, 80, 40), new RigidBody(1, 80, 40, 40, 1, 0.9f), new CubeCollider(40, 80, 40) });
	newEntity->GetTransform()->SetPosition(Vector3(150, 250, 0));
}
