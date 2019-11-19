#include "RigidbodySpawner.h"

RigidbodySpawner::RigidbodySpawner() : ILogicComponent()
{
	Time::timeScale = 5.0f; // For the sake of the demonstration

	superballTexture = ParticleRenderer::LoadTexture("Images/superball.png");
	pokeballTexture = ParticleRenderer::LoadTexture("Images/pokeball.png");
	ultraballTexture = ParticleRenderer::LoadTexture("Images/ultra-ball.png");

	Car1 = nullptr;
	Car2 = nullptr;
}


RigidbodySpawner::~RigidbodySpawner()
{
	if (superballTexture != NULL) {
		glDeleteTextures(1, &superballTexture);
	}

	if (pokeballTexture != NULL) {
		glDeleteTextures(1, &pokeballTexture);
	}

	if (ultraballTexture != NULL) {
		glDeleteTextures(1, &ultraballTexture);
	}
}

void RigidbodySpawner::Update(float deltaTime)
{
	SDL_Event* event = &SystemManager::GetSystemByType<EventSystem>()->event;
	switch (event->type) {
	case SDL_KEYDOWN:
		switch (event->key.keysym.sym) {
		case SDLK_a:
			SpawnRigidbodyTest(false);
			break;
		case SDLK_z:
			SpawnRigidbodyTest(true);
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

void RigidbodySpawner::SpawnRigidbodyTest(bool force)
{

	Entity* newEntity = EntityManager::CreateEntity("BasketBall", { new RigidBody(1, 80, 40, 40, 1, 0.9f), new CubeRenderer(80, 40, 40) });
	newEntity->GetTransform()->SetPosition(Vector3(150, 250, 0));

	if (force) {
		newEntity->GetComponentByType<RigidBody>()->AddForceAtBodyPoint(Vector3(0, 0, 100), Vector3(-10, 0, 0));
	}
	
}


void RigidbodySpawner::SpawnRigidbodyCar()
{

	Car1 = EntityManager::CreateEntity("BasketBall", { new RigidBody(1, 80, 40, 40, 1, 0.9f), new CubeRenderer(80, 40, 40) });
	Car1->GetTransform()->SetPosition(Vector3(50, 250, 0));

	Car2 = EntityManager::CreateEntity("VollzyBall", { new RigidBody(1, 100, 50, 50, 1, 0.9f), new CubeRenderer(100, 50, 50) });
	Car2->GetTransform()->SetPosition(Vector3(650, 250, 0));


	Car1->GetComponentByType<RigidBody>()->SetGravity(false);
	Car1->GetComponentByType<RigidBody>()->AddForceAtBodyPoint(Vector3(300, 0, 0), Vector3());


	Car2->GetComponentByType<RigidBody>()->SetGravity(false);
	Car2->GetComponentByType<RigidBody>()->AddForceAtBodyPoint(Vector3(-300, 0, 0), Vector3());

}


void RigidbodySpawner::RigidbodyCarCrash()
{
	if (Vector3::Distance(Car1->GetTransform()->GetPosition(), Car2->GetTransform()->GetPosition()) <= 180)
	{

		std::vector<float> r;
		for (int i = 0; i < 4; i++) { r.push_back(static_cast <float> (rand()) / static_cast <float> (RAND_MAX)); }

		Car1->GetComponentByType<RigidBody>()->ClearAccumForce();
		Car1->GetComponentByType<RigidBody>()->ClearAccumTorqueForce();
		Car1->GetComponentByType<RigidBody>()->AddForceAtBodyPoint(Vector3(-200 * r[0], 5* r[1], 0), Vector3(80, 0, 0));

		Car2->GetComponentByType<RigidBody>()->ClearAccumForce();
		Car2->GetComponentByType<RigidBody>()->ClearAccumTorqueForce();
		Car2->GetComponentByType<RigidBody>()->AddForceAtBodyPoint(Vector3(130 * r[2], 2* r[3], 0), Vector3(-100, 0, 0));
		checkCol = false;
	}

}
