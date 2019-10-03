#version 450 core

layout (location = 0) in vec3 Position;
layout (location = 1) in vec4 Color;
layout (location = 2) in vec2 TexCoords;

out vec4 fColor;
out vec2 fTexCoords;

void main()
{
	// Define homogene position
	gl_Position = vec4(Position , 1.0);

	// Tranfer given parameters to fragment shader
	fColor = Color;
	fTexCoords = TexCoords;
}