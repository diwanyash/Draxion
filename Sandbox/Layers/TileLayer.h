#pragma once
#include "DraxionMain.h"
class TileLayer : public Draxion::Layer
{
public:
	TileLayer();
	~TileLayer() {};

	void OnAttach() override;
	void OnUpdate(float dt) override;
	void OnImGuiRender() override;
	void OnEvent(Draxion::Event& e) override;
	//Test
	void Regen();
	void RegenWorldGrid();
	std::pair<int,int> SetDisplayGrid( int x, int y);
private:
	// Camera
	Draxion::OrthoGraphicCameraController m_Camera_Control = {1280.0f / 720.0f};

	// Texture
	Draxion::Ref<Draxion::Texture2D> m_Grass_Full         = nullptr;

	struct WorldGrid
	{
	public:
		enum TileType
		{
			Water = 0,
			Grass = 1,
		};
		WorldGrid(TileType type)
			:m_type(type)
		{}
		TileType GetType() const { return m_type; }
		void SetType( TileType type ) { m_type = type; }
	private:
		TileType m_type;
	};

public:
	std::pair<int, int> GetVector(WorldGrid::TileType BL, WorldGrid::TileType TL,
		WorldGrid::TileType TR, WorldGrid::TileType BR);

	struct TileMap
	{
		TileMap( int x, int y)
		{
			float TileWidth = 1.0f / 4.0f;
			float TileHeight = 1.0f / 4.0f;
		
			u0 = (float)x * TileWidth;
			v0 = (float)y * TileHeight;

			u1 = u0 + TileWidth;
			v1 = v0 + TileHeight;
		}
		glm::vec4 GetUVPos() { return glm::vec4(u0,v0,u1,v1); }
		float u0;
		float v0;
		float u1;
		float v1;
	};

	// Vector/Value
	glm::ivec2 m_GridLoc = {1,1};
	glm::vec2 MouseCamPos;
	glm::ivec2 HoveredTile = {0,0};
	
	// Window
	int Win_Width = 1280;
	int Win_Height = 720;

	// TileSet Info
	const int AtlasSize = 128;
	const int TileSize = 32;
	const int Gridx = 4;
	const int Gridy = 4;
	std::vector<Draxion::Ref<TileMap>> GridVec;
	std::vector<Draxion::Ref<WorldGrid>> WorldGridMap;

	// TestDisplayGridMap
	std::vector<std::pair<int,int>> DisplayGridMap;
	glm::vec4 MapSize = {0.0f,0.0f,0.0f,0.0f};
	int GridSize_x = 2;
	int GridSize_y = 2;
	int GridSize   = 2;
};
