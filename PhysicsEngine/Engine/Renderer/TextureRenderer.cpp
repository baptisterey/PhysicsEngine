#include "TextureRenderer.h"

#include "../Physic/Particle.h"

TextureRenderer::TextureRenderer() : BaseComponent(), IRendererComponent()
{

}


TextureRenderer::~TextureRenderer()
{

}

void TextureRenderer::Render(SDL_Renderer * renderer)
{
	// Where to draw the texture on the screen
	SDL_Rect destRect;

	destRect.h = 40;
	destRect.w = 40;

	Vector3 position = GetOwner()->GetPosition();

	destRect.x = (int) position.x;
	destRect.y = (int) position.y;

	SDL_RenderCopyEx(renderer, texture, NULL, &destRect, NULL, NULL, SDL_FLIP_NONE);
}

void TextureRenderer::SetTexture(SDL_Texture * _texture)
{
	if (_texture != nullptr) {
		texture = _texture;
	}
}

SDL_Texture* TextureRenderer::LoadTexture(std::string fileName, SDL_Renderer* renderer)
{
	SDL_Surface* tempSurface = IMG_Load(fileName.c_str());

	if (tempSurface != NULL) {
		SDL_Texture* _texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
		SDL_FreeSurface(tempSurface);

		return _texture;
	}

	return NULL;
}


