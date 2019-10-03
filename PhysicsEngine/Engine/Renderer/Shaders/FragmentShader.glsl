#version 450 core

//out vec4 FragColor;

in vec4 fColor;
in vec2 fTexCoords;

//uniform sampler2D Texture;

void main()
{
	//vec4 texColor = texture(Texture, fTexCoords); // Getting concerned pixel
    //if(texColor.a < 0.1) // Basic transparent discard. If real blending is needed, have a look at https://learnopengl.com/Advanced-OpenGL/Blending
    //    discard;
	gl_FragColor = vec4(0.0,1.0,0.0,1.0); // Colorize with vertex color
}