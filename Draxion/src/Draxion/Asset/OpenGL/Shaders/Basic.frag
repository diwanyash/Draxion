#version 410 core
layout (location = 0) out vec4 FragOut;

in vec4 v_Color;
in vec2 v_TexCoord;
in float v_TextureIndex;

uniform sampler2D u_Texture[32];

void main()
{
// int(v_TextureIndex)
	FragOut = texture( u_Texture[int(v_TextureIndex)], v_TexCoord ) * v_Color ;
	// FragOut = v_Color;
};