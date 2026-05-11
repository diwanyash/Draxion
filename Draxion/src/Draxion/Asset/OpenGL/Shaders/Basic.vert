#version 410 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 OurColor;
out vec2 TexCoord;

uniform mat4 u_ViewProjection;

void main()
{
	gl_Position = u_ViewProjection * vec4(aPos, 1.0);
	OurColor = aColor;
	TexCoord = aTexCoord;
};