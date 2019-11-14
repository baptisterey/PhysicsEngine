#include "CubeRenderer.h"

CubeRenderer::CubeRenderer() : BaseComponent(), IRendererComponent()
{
	texture = NULL;
	glGenVertexArrays(1, VAO);
	glGenBuffers(1, VBO);
	glGenBuffers(1, EBO);
}

CubeRenderer::~CubeRenderer()
{

}

void CubeRenderer::Render(GLuint programID, Matrix4 VP)
{
	// Where to draw the texture on the screen
	Vector3 position = GetOwner()->GetTransform()->GetPosition();
	Quaternion rotation = GetOwner()->GetTransform()->GetRotation();

	float
		w = 80,
		h = 40,
		p = 40,
		x = (int)position.x,
		y = (int)position.y,
		z = (int)position.z;
	

	Vector3
		p0 = rotation.rotatedVector(Vector3(w, h, -p)) + position,		// top right back
		p1 = rotation.rotatedVector(Vector3(w, -h, -p)) + position,		// bottom right back
		p2 = rotation.rotatedVector(Vector3(-w, -h, -p)) + position,		// bottom left back
		p3 = rotation.rotatedVector(Vector3(-w, h, -p)) + position,		// top left back
		p4 = rotation.rotatedVector(Vector3(w, h, p)) + position,		// top right front
		p5 = rotation.rotatedVector(Vector3(w, -h, p)) + position,		// bottom right front
		p6 = rotation.rotatedVector(Vector3(-w, -h, p)) + position,	// bottom left front
		p7 = rotation.rotatedVector(Vector3(-w, h, p)) + position;		// top left front

	float vertices[] = {
		// position					color (RGBA)		texture coords
		p0.x, p0.y, p0.z,			1.0, 1.0, 1.0,		-.1, -.1,		// top right back
		p1.x, p1.y, p1.z,			1.0, 1.0, 1.0,		-.1, -.1,		// bottom right back
		p2.x, p2.y, p2.z,			1.0, 1.0, 1.0,		-.1, -.1,		// bottom left back
		p3.x, p3.y, p3.z,			1.0, 1.0, 1.0,		-.1, -.1,		// top left back
		p4.x, p4.y, p4.z,			1.0, 1.0, 1.0,		-.1, -.1,		// top right front
		p5.x, p5.y, p5.z,			1.0, 1.0, 1.0,		-.1, -.1,		// bottom right front
		p6.x, p6.y, p6.z,			1.0, 1.0, 1.0,		-.1, -.1,		// bottom left front
		p7.x, p7.y, p7.z,			1.0, 1.0, 1.0,		-.1, -.1,		// top left front
	};

	GLubyte indices[] = {
		3, 2, 0, 0, 2, 1, // back face (with 2 triangles)
		4, 5, 7, 5, 6, 7, // front face
		7, 2, 3, 7, 6, 2, // left face
		4, 1, 5, 4, 0, 1, // right face
		2, 6, 5, 2, 5, 1, // bottom face
		3, 0, 4, 3, 4, 7  // top face
	};

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
	glUniformMatrix4fv(3, 1, false, (const float*)f);

	if (wireframe) {
		glPolygonMode(GL_FRONT, GL_POINT);
		glPolygonMode(GL_BACK, GL_LINE);
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	glDrawElements(GL_TRIANGLES, /*indices size : */ 36, GL_UNSIGNED_BYTE, 0);
}

void CubeRenderer::SetTexture(GLuint _texture)
{
	if (_texture != NULL) {
		texture = _texture;
	}
}

GLuint CubeRenderer::LoadTexture(std::string fileName)
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


