#pragma once

#include "../Math/Matrix4.h"
#include "../Base/BaseComponent.h"

#include <SDL.h>
#include <gl\glew.h>
#include <SDL_opengl.h>

class IRendererComponent : virtual public BaseComponent
{
public:
	IRendererComponent();
	virtual ~IRendererComponent();

	virtual void Render(GLuint programID, Matrix4 VP) {};
};

