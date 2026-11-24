#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 UVpos;

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 projection;
uniform vec4 uvrect;

void main()
{
	TexCoords = vec2((uvrect.x + UVpos.x * uvrect.z), (uvrect.y + UVpos.y * uvrect.w));
	gl_Position = projection * model * vec4(aPos, 1.0);
}