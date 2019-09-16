#pragma once

#include "../Base/BaseComponent.h"
#include "IRendererComponent.h"

#include <SDL.h>
#include <gl\glew.h>
#include <SDL_opengl.h>

class ParticleRenderer : public BaseComponent, public IRendererComponent
{
public:
	ParticleRenderer();
	~ParticleRenderer();

	void Render(SDL_Renderer* renderer);

	void SetTexture(SDL_Texture* texture);

	static SDL_Texture* LoadTexture(std::string fileName, SDL_Renderer* renderer);
private:

	SDL_Texture* texture = nullptr;
};

