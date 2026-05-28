#version 410 core
out vec4 FragOut;

in vec2 TexCoord;

uniform sampler2D u_Texture;
uniform vec4 u_Color;

void main()
{
	FragOut = texture(u_Texture, TexCoord  * 10.0f) * u_Color;
};