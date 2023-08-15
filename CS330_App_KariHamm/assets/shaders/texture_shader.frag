#version 330 core
		
out vec4 FragColor;
in vec4 vertexColor;
in vec2 texCoord;

uniform sampler2D tex0;		// GL_TEXTURE0
uniform sampler2D tex1;		// GL_TEXTURE1

void main()
{
	FragColor = mix(texture(tex0, texCoord), texture(tex1, texCoord), 0.0) * vertexColor; 
}