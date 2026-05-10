#version 410 core
out vec4 FragOut;

in vec3 OurColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;

vec4 temp;

void main()
{
	temp = texture(ourTexture, TexCoord);
	FragOut = vec4(1 - temp.xyz, 1.0);
};