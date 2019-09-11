#include "TextureRenderer.h"

#include "Particle.h"

TextureRenderer::TextureRenderer() : BaseComponent(), IRendererComponent()
{

}


TextureRenderer::~TextureRenderer()
{
	if (texture != nullptr) {
		SDL_DestroyTexture(texture);
	}
}

void TextureRenderer::Render(SDL_Renderer * renderer)
{
	if (texture == nullptr) {
		return;
	}

	Particle* particle = GetOwner()->GetComponentByType<Particle>();

	// What part of the texture is to draw
	SDL_Rect srcRect;
	srcRect.x = 0;
	srcRect.y = 0;

	srcRect.h = imageSizeHeight;
	srcRect.w = imageSizeWeight;

	// Where to draw the texture on the screen
	SDL_Rect destRect;

	destRect.h = 35;
	destRect.w = 35;

	destRect.x = particle->position.x;
	destRect.y = particle->position.y;

	SDL_RenderCopyEx(renderer, texture, &srcRect, &destRect, NULL, NULL, SDL_FLIP_NONE);
}

void TextureRenderer::LoadTexture(std::string fileName, SDL_Renderer* renderer)
{
	SDL_Surface* tempSurface = IMG_Load(fileName.c_str());

	if (tempSurface != NULL) {
		SDL_Texture* _texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
		
		SDL_QueryTexture(_texture, NULL, NULL, &imageSizeWeight, &imageSizeHeight);

		texture = _texture;
		SDL_FreeSurface(tempSurface);
	}
}


