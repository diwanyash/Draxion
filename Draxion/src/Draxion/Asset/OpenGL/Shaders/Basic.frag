#version 410 core
out vec4 FragOut;

in vec2 TexCoord;

uniform sampler2D u_Texture;
uniform float u_Alpha;

void main()
{
	vec4 PrePro = texture(u_Texture, TexCoord);
	if( PrePro.w != 0.0f)
	{
		FragOut = vec4(PrePro.xyz, u_Alpha);
	}
	else
	{
		FragOut = PrePro;
	}
};