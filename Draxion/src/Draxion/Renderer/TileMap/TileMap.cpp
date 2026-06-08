#include "TileMap.h"
#include "Draxion/Renderer/Renderer2D.h"

namespace Draxion
{
	static const std::pair<int, int> TileLookup[16] =
	{
		{0,0}, // 0000 0 
		{1,0}, // 0001 1
		{0,1}, // 0010 2
		{1,3}, // 0011 3

		{3,0}, // 0100 4
		{0,2}, // 0101 5
		{1,1}, // 0110 6
		{2,1}, // 0111 7

		{0,3}, // 1000 8 
		{3,3}, // 1001 9 
		{2,0}, // 1010 10
		{1,2}, // 1011 11

		{3,1}, // 1100 12
		{2,3}, // 1101 13
		{3,2}, // 1110 14
		{2,2}, // 1111 15
	};

	TileMap::TileMap(const std::string& TextMap, const std::string& TileSetTexPath, const  glm::ivec2& MapSize, const glm::ivec2& TextureDiv, const  glm::vec3& Position)
		:
		m_TextMap(TextMap),
		m_MapSize(MapSize),
		m_TextureDiv(TextureDiv),
		m_Position(Position)
	{
		m_TileSetTexture = Texture2D::Create(TileSetTexPath);
		m_Tiles.resize( m_TextureDiv.x * m_TextureDiv.y);
		for (int y = 0; y < m_TextureDiv.y; y ++)
		{
			for (int x = 0; x < m_TextureDiv.x; x++)
			{
				m_Tiles[y * m_TextureDiv.x + x ] = CalculateTilesUV( x, y );
			}
		}
		m_DisplayMap.resize((m_MapSize.x - 1) * (m_MapSize.y - 1));
		DisplayGridMapGen();
	}

	void TileMap::Draw( float dt ) const
	{
		for (int y = 0; y < m_MapSize.y - 1; y++)
		{
			for (int x = 0; x < m_MapSize.x - 1; x++)
			{
				auto pair = m_DisplayMap[y * (m_MapSize.x - 1) + x];
				int grid_x = pair.first;
				int grid_y = pair.second;

				Renderer2D::DrawSquare(m_TileSetTexture, { float(x) + m_Position.x,float(y) + m_Position.y,0.0f },
					glm::vec4(m_Tiles[grid_y * 4 + grid_x]), { 1.0f,1.0f });

			}
		}
	}

	glm::vec4 TileMap::CalculateTilesUV(int x, int y) const
	{
		float TileWidth = 1.0f / (float)m_TextureDiv.x;
		float TileHeight = 1.0f / (float)m_TextureDiv.y;

		float u0 = (float)x * TileWidth;
		float v0 = (float)y * TileHeight;

		float u1 = u0 + TileWidth;
		float v1 = v0 + TileHeight;

		return glm::vec4( u0,v0, u1, v1 );
	}

	void TileMap::DisplayGridMapGen() 
	{
		for (int y = 0; y < m_MapSize.y - 1; y++)
		{
			for (int x = 0; x < m_MapSize.x - 1; x++)
			{
				m_DisplayMap[y * (m_MapSize.x - 1) + x] = SetDisplayGrid(x, y);//{ Draxion::RandomGen::Get<int>(0, 3),Draxion::RandomGen::Get<int>(0, 3) };
			}
		}
	}

	std::pair<int, int> TileMap::SetDisplayGrid( int x, int y ) const
	{
		// Flip The Y-axis as string read from Top->Bottom
		int row0 = (m_MapSize.y - 1 - y);
		int row1 = (m_MapSize.y - 2 - y);

		TileType BL = m_TextMap[row0 * m_MapSize.x + x] == 'G' ? TileType::Grass : TileType::Water ;
		TileType TL = m_TextMap[row1 * m_MapSize.x + x] == 'G' ? TileType::Grass : TileType::Water;
		TileType TR = m_TextMap[row1 * m_MapSize.x + (x + 1)] == 'G' ? TileType::Grass : TileType::Water;
		TileType BR = m_TextMap[row0 * m_MapSize.x + (x + 1)] == 'G' ? TileType::Grass : TileType::Water;

		uint8_t mask = 0;

		if (BL == TileType::Grass)
			mask |= (1 << 3);

		if (TL == TileType::Grass)
			mask |= (1 << 2);

		if (TR == TileType::Grass)
			mask |= (1 << 1);

		if (BR == TileType::Grass)
			mask |= (1 << 0);

		return TileLookup[mask];
	}

}
