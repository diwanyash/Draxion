#version 410 core
out vec4 FragOut;

in vec3 OurColor;
in vec2 TexCoord;

uniform sampler2D u_Texture;

void main()
{
	FragOut = texture(u_Texture, TexCoord);
};