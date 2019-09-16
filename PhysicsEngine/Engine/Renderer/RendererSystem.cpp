#include "RendererSystem.h"

RendererSystem::RendererSystem() : ISystem()
{
	context = NULL;
	window = nullptr;
}

RendererSystem::~RendererSystem()
{
	close();
}

void RendererSystem::Update()
{
	glClear(GL_COLOR_BUFFER_BIT);

	for (IRendererComponent* component : components) {
		;//component->Render(renderer); TODO
	}

	SDL_GL_SwapWindow(window);
}

void RendererSystem::AddRendererComponent(IRendererComponent* component)
{
	if (component != nullptr) {
		components.push_back(component);
	}
}

void RendererSystem::RemoveRendererComponent(IRendererComponent* component)
{
	components.erase(std::remove(components.begin(), components.end(), component), components.end());
}

bool RendererSystem::InitRenderer(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	// Window creation
	int flags = SDL_WINDOW_OPENGL;
	if (fullscreen) {
		flags |= SDL_WINDOW_FULLSCREEN;
	}

	window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
	if (!window) {
		printf("Failed to init SDL Window !");
		return false;
	}

	// OpenGL initialization
	context = SDL_GL_CreateContext(window);

	// Set OpenGL version.
	// SDL_GL_CONTEXT_CORE gives only the newer version, deprecated functions are disabled
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	// 3.2 is part of the modern versions of OpenGL, but most video cards are able to run it
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

	// Turn on double buffering with a 24bit Z buffer. Might need to change this to 16 or 32 for the system.
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	// This makes the buffer swap syncronized with the monitor's vertical refresh
	SDL_GL_SetSwapInterval(1);

	// Init GLEW
	// Apparently, this is needed only for Apple.
#ifndef __APPLE__
	glewExperimental = GL_TRUE;
	glewInit();
#endif


	// Define the background
	glClearColor(.1f, .1f, .1f, 1.0);
	// Clear the content of the screen
	glClear(GL_COLOR_BUFFER_BIT);
	// Actually draw things on screen
	SDL_GL_SwapWindow(window);

	return true;
}

void RendererSystem::close()
{
	// glDeleteProgram(programID);
	// glDeleteTextures(1, &textureID);

	SDL_GL_DeleteContext(context);

	// Close and destroy the window
	SDL_DestroyWindow(window);

	// Clean up
	SDL_Quit();
}