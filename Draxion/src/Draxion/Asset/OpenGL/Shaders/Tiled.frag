#version 410 core
out vec4 FragOut;

in vec2 TexCoord;

uniform sampler2D u_Texture;
uniform ivec2 u_Grid;
uniform vec4 u_Color;

const vec2 TileSize = vec2(1.0 / 4.0);

void main()
{
    vec2 TileOffset = vec2(u_Grid) * TileSize;

    vec2 UV = TileOffset + (TexCoord * TileSize);

    FragOut = texture(u_Texture, UV) ;
}