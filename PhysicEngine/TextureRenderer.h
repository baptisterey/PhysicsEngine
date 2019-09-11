#pragma once

#include "BaseComponent.h"
#include "IRendererComponent.h"

#include <SDL.h>
#include "SDL_image.h"

class TextureRenderer : public BaseComponent, public IRendererComponent
{
public:
	TextureRenderer();
	~TextureRenderer();

	void Render(SDL_Renderer* renderer);

	void SetTexture(SDL_Texture* texture);

	static SDL_Texture* LoadTexture(std::string fileName, SDL_Renderer* renderer);
private:

	SDL_Texture* texture = nullptr;
};

