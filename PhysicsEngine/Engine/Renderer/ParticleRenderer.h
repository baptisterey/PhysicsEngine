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

	void Render();

	void SetTexture(GLuint texture);

	static GLuint LoadTexture(std::string fileName);
private:

	GLuint texture;
};

