#pragma once

#include <SDL.h>
#include <gl\glew.h>
#include <SDL_opengl.h>

class IRendererComponent
{
public:
	IRendererComponent();
	virtual ~IRendererComponent();

	virtual void Render(GLuint programID) {};
};

