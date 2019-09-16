#include "ParticleRenderer.h"

#include "../Physic/Particle.h"

ParticleRenderer::ParticleRenderer() : BaseComponent(), IRendererComponent()
{

}


ParticleRenderer::~ParticleRenderer()
{

}

void ParticleRenderer::Render(SDL_Renderer * renderer)
{
	Particle* particle = GetOwner()->GetComponentByType<Particle>();

	// Where to draw the texture on the screen
	SDL_Rect destRect;

	destRect.h = 40;
	destRect.w = 40;

	destRect.x = (int) particle->position.x;
	destRect.y = (int) particle->position.y;

	SDL_RenderCopyEx(renderer, texture, NULL, &destRect, NULL, NULL, SDL_FLIP_NONE);
}

void ParticleRenderer::SetTexture(SDL_Texture * _texture)
{
	if (_texture != nullptr) {
		texture = _texture;
	}
}

SDL_Texture* ParticleRenderer::LoadTexture(std::string fileName, SDL_Renderer* renderer)
{
	SDL_Surface* tempSurface = NULL;//IMG_Load(fileName.c_str()); TODO

	if (tempSurface != NULL) {
		SDL_Texture* _texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
		SDL_FreeSurface(tempSurface);

		return _texture;
	}

	return NULL;
}


