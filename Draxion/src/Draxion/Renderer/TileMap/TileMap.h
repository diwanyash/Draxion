#pragma once
#include <string>
#include <glm/glm.hpp>
#include "Draxion/Renderer/Texture.h"

namespace Draxion
{
	class TileMap
	{
	public:
		TileMap() = default;
		TileMap( const std::string& TextMap, const std::string& TileSetTexPath,const glm::ivec2& MapSize, const  glm::ivec2& TextureDiv, const  glm::vec3& Position );
		
		void Draw( float dt ) const;
	
		enum TileType
		{
			Water = 0,
			Grass = 1,
		};
	private:
		Ref<Texture2D> m_TileSetTexture;
		glm::ivec2 m_TextureDiv;
		std::string m_TextMap;
		glm::vec2 m_MapSize;
		std::vector<std::pair<int, int>> m_DisplayMap;
		glm::vec3 m_Position = { 0.0f,0.0f,0.0f };
	private:
		glm::vec4 CalculateTilesUV( int x, int y) const;
		void DisplayGridMapGen();
		std::pair<int, int> SetDisplayGrid( int x, int y ) const;
		std::vector<glm::vec4> m_Tiles;
	};

}