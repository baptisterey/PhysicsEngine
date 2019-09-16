#include "ParticleRenderer.h"

#include "../Physic/Particle.h"

ParticleRenderer::ParticleRenderer() : BaseComponent(), IRendererComponent()
{

}


ParticleRenderer::~ParticleRenderer()
{

}

void ParticleRenderer::Render(SDL_Renderer* renderer)
{
	Particle* particle = GetOwner()->GetComponentByType<Particle>();

	// Where to draw the texture on the screen
	SDL_Rect destRect;

	destRect.h = 40;
	destRect.w = 40;

	destRect.x = (int)particle->position.x;
	destRect.y = (int)particle->position.y;

	SDL_RenderCopyEx(renderer, texture, NULL, &destRect, NULL, NULL, SDL_FLIP_NONE);

	// Vertices
	float vertices[] = { 0.0, 0.0,	0.1, 0.0,	0.0, 0.1,		// Triangle 1
						 0.0, 0.0,	-0.1, 0.0,	0.0, -0.1 };	// Triangle 2

	// On remplie puis on active le tableau Vertex Attrib 0
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, vertices);
	glEnableVertexAttribArray(0);

	// On affiche des triangles
	glDrawArrays(GL_TRIANGLES, 0, 6);

	// On désactive le tableau Vertex Attrib puisque l'on n'en a plus besoin
	glDisableVertexAttribArray(0);
}

void ParticleRenderer::SetTexture(SDL_Texture* _texture)
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


