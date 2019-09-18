#include "ParticleRenderer.h"

#include "../Physic/Particle.h"
#include <SDL_image.h>

ParticleRenderer::ParticleRenderer() : BaseComponent(), IRendererComponent()
{
	texture = NULL;
}


ParticleRenderer::~ParticleRenderer()
{

}

void ParticleRenderer::Render()
{
	Particle* particle = GetOwner()->GetComponentByType<Particle>();

	// Where to draw the texture on the screen
	float
		w = 40,
		h = 40,
		x = (int)particle->position.x,
		y = (int)particle->position.y;

	// Vertices & texture coords
	float vertices[] = {
		0.0, 0.0,
		w, 0.0,
		w, h,
		0.0, h
	};
	float texCoords[] = {
		0.0, 0.0,
		1.0, 0.0,
		1.0, 1.0,
		0.0, 1.0
	};

	// Choose base color to draw
	glColor3f(1, 1, 1);
	// Apply a texture
	glBindTexture(GL_TEXTURE_2D, texture);
	// Start drawing
	glBegin(GL_QUADS);
	for (unsigned int i = 0; i < std::size(vertices); i += 2) {
		glTexCoord2f(texCoords[i], texCoords[i + 1]);
		glVertex3f(
			x + vertices[i],		// x
			y + vertices[i + 1],	// y
			0						// z --> to change when goin' further in 3D
		);
	}
	glEnd();
}

void ParticleRenderer::SetTexture(GLuint _texture)
{
	if (_texture != NULL) {
		texture = _texture;
	}
}

GLuint ParticleRenderer::LoadTexture(std::string fileName)
{
	SDL_Surface* tempSurface = IMG_Load(fileName.c_str());

	if (tempSurface != NULL) {
		GLuint tex;
		glGenTextures(1, &tex);
		glBindTexture(GL_TEXTURE_2D, tex);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, tempSurface->format->BytesPerPixel, tempSurface->w, tempSurface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, tempSurface->pixels);
		return tex;
	}

	return NULL;
}


