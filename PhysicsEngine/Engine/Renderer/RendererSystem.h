#pragma once
#include "../Base/ISystem.h"
#include "../Utils/Utils.h"
#include "IRendererComponent.h"

#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <streambuf>

#include <SDL.h>
#include <stdio.h>
#include <string>
#include <GL\glew.h>
#include <SDL_opengl.h>

#include "Camera.h"

class RendererSystem : public ISystem
{
public:
	RendererSystem();
	~RendererSystem();

	void Update();

	void AddRendererComponent(IRendererComponent* component);
	void RemoveRendererComponent(IRendererComponent* component);

	bool InitRenderer(const char * title, int xpos, int ypos, int width, int height, bool fullscreen);

private:
	std::vector<IRendererComponent*> components;

	void close();

	//Screen dimension constants
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;

	SDL_Window* window;
	SDL_GLContext context;
	GLuint programID;
	Camera* mainCamera;
};

