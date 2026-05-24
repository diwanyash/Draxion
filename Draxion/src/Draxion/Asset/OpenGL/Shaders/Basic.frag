#version 410 core
out vec4 FragOut;

in vec2 TexCoord;

uniform sampler2D u_Texture;
uniform float u_Alpha;

void main()
{
	FragOut = texture(u_Texture, TexCoord);
	// if( PrePro.w != 0.0f)
	// {
	//	   FragOut = vec4(PrePro.xyz, 1.0f);
	// }
	// else
	// {
	// 	   FragOut = PrePro;
	// }
};