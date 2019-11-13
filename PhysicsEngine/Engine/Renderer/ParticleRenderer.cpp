#include "ParticleRenderer.h"

ParticleRenderer::ParticleRenderer() : BaseComponent(), IRendererComponent()
{
	texture = NULL;
	glGenVertexArrays(1, VAO);
	glGenBuffers(1, VBO);
	glGenBuffers(1, EBO);
}

ParticleRenderer::~ParticleRenderer()
{

}

void ParticleRenderer::Render(GLuint programID, Matrix4 VP)
{
	// Where to draw the texture on the screen
	Vector3 position = GetOwner()->GetPosition();
	float
		w = 40,
		h = 40,
		x = (int)position.x,
		y = (int)position.y,
		z = (int)position.z;


	float vertices[] = {
		// position			color (RGBA)		texture coords
		x + w, y + h, z,	1.0, 1.0, 1.0,		0.0, 0.0,		// top right
		x + w, y, z,		1.0, 1.0, 1.0,		0.0, 1.0,		// bottom right
		x, y, z,			1.0, 1.0, 1.0,		1.0, 1.0,		// bottom left
		x, y + h, z,		1.0, 1.0, 1.0,		1.0, 0.0		// top left
	};

	GLubyte indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

	Vector3
		op_tr(vertices[0], vertices[1], vertices[2]), op_br(vertices[8], vertices[9], vertices[10]), 
		op_bl(vertices[16], vertices[17], vertices[18]), op_tl(vertices[24], vertices[25], vertices[26]),
		np_tr = VP.TransformPoint(op_tr), np_br = VP.TransformPoint(op_br), np_bl = VP.TransformPoint(op_bl), np_tl = VP.TransformPoint(op_tl),
		c_1 = np_tr / np_tr.z,
		c_2 = np_br / np_br.z,
		c_3 = np_bl / np_bl.z,
		c_4 = np_tl / np_tl.z;

	// Set up buffer arrays
	glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	// Define 'position' location in vertex shader
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// Define 'color' location in vertex shader
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// Define 'textureCoords' location in vertex shader
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindTexture(GL_TEXTURE_2D, texture);
	float f[4][4];
	VP.getTransformedMatrix(f);
	glUniformMatrix4fv(3, 1, false, (const float*) f);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0);
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
		glGenerateMipmap(GL_TEXTURE_2D);
		return tex;
	}

	return NULL;
}


