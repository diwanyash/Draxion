#version 410 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in float aTextureIndex;

out vec4 v_Color;
out vec2 v_TexCoord;
out float v_TextureIndex;

uniform mat4 u_ViewProjection;
//uniform mat4 u_Transform;

void main()
{
	v_Color = aColor;
	v_TexCoord = aTexCoord;
	v_TextureIndex = aTextureIndex;
	gl_Position = (u_ViewProjection) * vec4(aPos.xyz, 1.0f);
};