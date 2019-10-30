#pragma once
#include "../Engine/Base/BaseComponent.h"
#include "../Engine/Logic/ILogicComponent.h"

#include "../Engine/Managers/EntityManager.h"
#include "../Engine/Managers/SystemManager.h"
#include "../Engine/Physic/ForceGenerators/Spring.h"
#include "../Engine/Physic/Particle.h"
#include "../Engine/Renderer/ParticleRenderer.h"
#include "../Engine/Renderer/RendererSystem.h"
#include "../Engine/Utils/Time.h"

#include "../Engine/EventSystem.h"
#include "../Engine/Managers/SystemManager.h"

#include "../Engine/Physic/ForceGenerators/Buoyancy.h"
#include "KeyController.h"

#include "../Engine/Physic/ContactGenerators/CableContact.h"
#include "../Engine/Physic/ContactGenerators/RodContact.h"

#include <SDL.h>
#include <iostream>

class BallSpawner : public ILogicComponent
{
public:
    BallSpawner();
    ~BallSpawner();

    void Update(float deltaTime);

private:
    void SpawnSuperBall();
    void SpawnPokeBall();
    void SpawnUltraBall();

    void SpawnUltraBallSpring();
    void SpawnSuperBallBuoyancy();
    void SpawnSuperBallRod();

    GLuint ultraballTexture = NULL;
    GLuint superballTexture = NULL;
    GLuint pokeballTexture = NULL;
};