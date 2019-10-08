#include "Blob.h"

Blob::Blob() : nbParticles(0), k(0), core(NULL)
{
}

Blob::Blob(int nbParticles, float k) : nbParticles(nbParticles), k(k), core(NULL)
{
	SDL_Renderer* renderer = SystemManager::GetSystemByType<RendererSystem>()->GetRenderer();

	superballTexture = TextureRenderer::LoadTexture("./Images/superball.png", renderer);
	pokeballTexture = TextureRenderer::LoadTexture("./Images/pokeball.png", renderer);
	ultraballTexture = TextureRenderer::LoadTexture("./Images/ultra-ball.png", renderer);
}

Blob::~Blob()
{
}

void Blob::Update(float deltaTime)
{
	if (!isInit) {
		//Init Core particle
		core = new Particle(Vector3(0, 0, 0), 1, 0.1f, 0);
		GetOwner()->AddComponent(core);
		GetOwner()->AddComponent(new TextureRenderer());
		GetOwner()->GetComponentByType<TextureRenderer>()->SetTexture(superballTexture);
		GetOwner()->SetPosition(Vector3(300, 500, 0));
		GetOwner()->name = "BlobCore";

		//Init movement
		GetOwner()->AddComponent(new KeyController());

		//Init surrounding particles
		Vector3 corePos = core->GetOwner()->GetPosition();
		int distance = 60;
		float slice = 2 * std::_Pi * nbParticles;
		for (int i = 0; i < nbParticles; i++)
		{
			float angle = i * slice;
			Entity* newEntity = EntityManager::CreateEntity("BlobParticle", { new Particle(Vector3(0, 0, 0), 0.1 , 0.1, 0), new TextureRenderer(), new Spring(k, distance , core) });
			newEntity->SetPosition(Vector3(corePos.x + distance * sin(angle), corePos.y + distance * cos(angle), corePos.z));

			newEntity->GetComponentByType<TextureRenderer>()->SetTexture(pokeballTexture);
			particles.push_back(newEntity->GetComponentByType<Particle>());
		}
		isInit = true;
		return;
	}
}