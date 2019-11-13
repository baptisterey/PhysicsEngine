#pragma once

#include "../Base/BaseComponent.h"
#include "../Physic/Particle.h"
#include "../Math/Matrix4.h"
#include "IRendererComponent.h"

#include <SDL.h>
#include <gl\glew.h>
#include <SDL_opengl.h>
#include <SDL_image.h>

class CubeRenderer : public IRendererComponent
{
public:
	CubeRenderer();
	~CubeRenderer();

	void Render(GLuint programID, Matrix4 VP);

	void SetTexture(GLuint texture);

	static GLuint LoadTexture(std::string fileName);

	bool wireframe = true;
private:

	GLuint texture;
	GLuint VAO[1], VBO[1], EBO[1];
};

