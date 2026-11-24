#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture1;
uniform vec4 multiplier;

void main() 
{
	vec4 color = texture(texture1, TexCoords).rgba * multiplier;

	FragColor = color;
}