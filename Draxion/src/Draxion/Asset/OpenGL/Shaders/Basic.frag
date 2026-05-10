#version 410 core
out vec4 FragOut;

in vec3 OurColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;

void main()
{
	FragOut = texture(ourTexture, TexCoord);
};