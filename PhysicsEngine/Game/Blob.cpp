#include "Blob.h"

Blob::Blob() : nbParticles(0), k(0), core(NULL)
{
}

Blob::Blob(int nbParticles, float k) : nbParticles(nbParticles), k(k), core(NULL)
{
	slimeBall = ParticleRenderer::LoadTexture("./Images/Slimeball.png");
	blobCore = ParticleRenderer::LoadTexture("./Images/Magma_Cream.png");
}

Blob::~Blob()
{
}

void Blob::Update(float deltaTime)
{
	if (!isInit) {
		Init();
		isInit = true;
		return;
	}

	SDL_Event* event = &SystemManager::GetSystemByType<EventSystem>()->event;
	switch (event->type) {
	case SDL_KEYDOWN:
		switch (event->key.keysym.sym) { // Blob particle separation
		case SDLK_SPACE:

			isComplete = !isComplete;

			for (auto particle : particles) { // Activates and deactivates springs
				Spring* spring = particle->GetOwner()->GetComponentByType<Spring>();
				if (spring != nullptr) {
					spring->SetActive(isComplete);
				}

				if (isComplete == false) { // Deactivates cables
					CableContact* cableContact = particle->GetOwner()->GetComponentByType<CableContact>();
					if (cableContact != nullptr) {
						cableContact->SetActive(isComplete);
					}
				}

				float newMass = !isComplete ? 1 : 0.1;
				particle->SetMass(newMass);
			}
			break;
		}
	}

	if (isComplete) {
		for (auto particle : particles) { //Reactivates cable when in range
			if (Vector3::Distance(core->GetOwner()->GetTransform()->GetPosition(), particle->GetOwner()->GetTransform()->GetPosition()) <= cableLength) {
				CableContact* cableContact = particle->GetOwner()->GetComponentByType<CableContact>();
				if (cableContact != nullptr && !cableContact->IsActive()) {
					cableContact->SetActive(true);
				}
			}
		}
	}
}

void Blob::Init()
{
	//Init Core particle
	core = new Particle(Vector3(0, 0, 0), 2, 0.1f, 0);
	GetOwner()->AddComponent(core);
	GetOwner()->AddComponent(new ParticleRenderer());
	GetOwner()->GetComponentByType<ParticleRenderer>()->SetTexture(blobCore);
	GetOwner()->GetTransform()->SetPosition(Vector3(500, 550, 0));
	GetOwner()->name = "BlobCore";

	//Init movement
	GetOwner()->AddComponent(new KeyController());

	//Init surrounding particles
	Vector3 corePos = core->GetOwner()->GetTransform()->GetPosition();
	int distance = 60;
	float slice = 2 * std::_Pi * nbParticles;
	for (int i = 0; i < nbParticles; i++)
	{
		float angle = i * slice;
		Entity* newEntity = EntityManager::CreateEntity("BlobParticle", { new Particle(Vector3(0, 0, 0), 0.2, 0.1, 0), new ParticleRenderer(), new Spring(k, distance , core), new CableContact(cableLength, 0.75f, core) });
		newEntity->GetTransform()->SetPosition(Vector3(corePos.x + distance * sin(angle), corePos.y + distance * cos(angle), corePos.z));

		newEntity->GetComponentByType<ParticleRenderer>()->SetTexture(slimeBall);
		particles.push_back(newEntity->GetComponentByType<Particle>());
	}
}