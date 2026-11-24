#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture1;
uniform vec4 multiplier;
uniform int whiteException;

void main() 
{
	vec4 color = texture(texture1, TexCoords).rgba;
	if (!(whiteException == 1 && all(greaterThan(color.xyz, vec3(0.98f, 0.98f, 0.98f)))))
	{
		color = color * multiplier;
	}

	FragColor = color;
}