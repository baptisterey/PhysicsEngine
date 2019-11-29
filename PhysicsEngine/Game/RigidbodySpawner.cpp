#include "RigidbodySpawner.h"

RigidbodySpawner::RigidbodySpawner() : ILogicComponent()
{
	Time::timeScale = 5.0f; // For the sake of the demonstration

	Car1 = nullptr;
	Car2 = nullptr;


	float
		size = 1000,
		midSize = size / 2;

	Entity* newEntity = EntityManager::CreateEntity("Tree", { new CubeRenderer(size, size, size) });
	newEntity->GetTransform()->SetPosition(Vector3(-midSize, -midSize, -midSize));
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
		case SDLK_g:
			SpawnRigidbodyCar();
		}

		break;
	}

	if (Car1 != nullptr && Car2 != nullptr)
	{
		RigidbodyCarCrash();
	}
}

void RigidbodySpawner::SpawnRigidbodyTest()
{

	Entity* newEntity = EntityManager::CreateEntity("BasketBall", { new RigidBody(1, 80, 40, 40, 1, 0.9f), new CubeRenderer(80, 40, 40), new CubeCollider(80, 40, 40) });
	newEntity->GetTransform()->SetPosition(Vector3(150, 250, 0));

	newEntity->GetComponentByType<RigidBody>()->AddForceAtBodyPoint(Vector3(0, 450, 100), Vector3(-8, 8, 0));
}

void RigidbodySpawner::SpawnRigidbodyTest2()
{
	Entity* newEntity = EntityManager::CreateEntity("BasketBall", { new RigidBody(1, 80, 40, 40, 1, 0.95f), new CubeRenderer(80, 55, 40), new CubeCollider(80, 55, 40) });
	newEntity->GetTransform()->SetPosition(Vector3(150, 250, 0));

	newEntity->GetComponentByType<RigidBody>()->AddForceAtBodyPoint(Vector3(250, 450, 0), Vector3(-8, 8, 6));
}


void RigidbodySpawner::SpawnRigidbodyCar()
{

	Car1 = EntityManager::CreateEntity("BasketBall", { new RigidBody(1, 80, 40, 40, 1, 0.65f), new CubeRenderer(80, 40, 40), new CubeCollider(80, 40, 40) });
	Car1->GetTransform()->SetPosition(Vector3(50, 250, 0));

	Car2 = EntityManager::CreateEntity("VollzyBall", { new RigidBody(1, 100, 50, 50, 1, 0.65f), new CubeRenderer(100, 50, 50), new CubeCollider(100, 50, 50) });
	Car2->GetTransform()->SetPosition(Vector3(650, 250, 0));


	Car1->GetComponentByType<RigidBody>()->SetGravity(false);
	Car1->GetComponentByType<RigidBody>()->AddForceAtBodyPoint(Vector3(1000, 0, 0), Vector3());


	Car2->GetComponentByType<RigidBody>()->SetGravity(false);
	Car2->GetComponentByType<RigidBody>()->AddForceAtBodyPoint(Vector3(-1000, 0, 0), Vector3());

}


void RigidbodySpawner::RigidbodyCarCrash()
{
	if (Vector3::Distance(Car1->GetTransform()->GetPosition(), Car2->GetTransform()->GetPosition()) <= 180)
	{

		Vector3 crashPosition = Car2->GetTransform()->GetPosition();
		crashPosition.x -= 100;
		crashPosition.y -= 8;
		crashPosition.z -= 3;
		
		Car1->GetComponentByType<RigidBody>()->ResetVelocityAndAcceleration();
		Car1->GetComponentByType<RigidBody>()->AddForceAtPoint(Vector3(-350, 10, 0), crashPosition);

		Car2->GetComponentByType<RigidBody>()->ResetVelocityAndAcceleration();
		Car2->GetComponentByType<RigidBody>()->AddForceAtPoint(Vector3(350, 10, 0), crashPosition);
		checkCol = false;

		Car1->GetComponentByType<RigidBody>()->SetLinearDamping(0.5f);
		Car2->GetComponentByType<RigidBody>()->SetLinearDamping(0.5f);
	}

}
