#version 410 core
out vec4 FragOut;

uniform vec4 u_Color;

void main()
{
	FragOut = u_Color;
};