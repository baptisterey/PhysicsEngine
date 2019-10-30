#version 450 core

in vec4 fColor;
in vec2 fTexCoords;

uniform sampler2D Texture;

void main()
{
	vec4 texColor = texture(Texture, fTexCoords); // Getting concerned pixel
    if(texColor.a < 0.1) // Basic transparent discard. If real blending is needed, have a look at https://learnopengl.com/Advanced-OpenGL/Blending
        discard;
	gl_FragColor = fColor * texColor; // Colorize with vertex color
}