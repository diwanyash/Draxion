#version 410 core
layout (location = 0) out vec4 FragOut;


in vec4 v_Color;
in vec2 v_TexCoord;
in float v_TextureIndex;

// investigate int/uint is not varying in..... for u_Grid
uniform sampler2D u_Texture[32];
uniform ivec2 u_Grid;

const vec2 TileSize = vec2(1.0 / 4.0);

void main()
{
    vec2 TileOffset = vec2(u_Grid) * TileSize; 

    vec2 UV = TileOffset + (v_TexCoord * TileSize);

    // FragOut = texture(u_Texture[int(v_TextureIndex)], UV) * v_Color ;
    FragOut = texture(u_Texture[int(v_TextureIndex)], UV) * v_Color;
    // FragOut = v_Color;
}