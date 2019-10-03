#pragma once

#include "../Base/BaseComponent.h"
#include "../Physic/Particle.h"
#include "IRendererComponent.h"
#include "Shaders/VertexData.h"

#include <SDL.h>
#include <gl\glew.h>
#include <SDL_opengl.h>
#include <SDL_image.h>

class ParticleRenderer : public BaseComponent, public IRendererComponent
{
public:
	ParticleRenderer();
	~ParticleRenderer();

	void Render(GLuint programID);

	void SetTexture(GLuint texture);

	static GLuint LoadTexture(std::string fileName);
private:

	GLuint texture;
	GLuint VAO[1], VBO[1], EBO[1];
};

