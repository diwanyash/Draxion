#pragma once
#include "DraxionMain.h"
#include "Draxion/Renderer/TileMap/TileMap.h"
#include "Draxion/Renderer/Sprite/Player.h"

class TileMapLayer : public Draxion::Layer
{
public:
	TileMapLayer();
	~TileMapLayer() {};

	void OnAttach() override;
	void OnDetach() override;
	void OnUpdate( float dt ) override;
	void OnEvent( Draxion::Event& e ) override;
	void OnImGuiRender() override;
private:
	// Camera
	Draxion::OrthoGraphicCameraController m_Camera_Con = { 1280.0f / 720.0f };
	// Texture
	std::string m_Grass_Full = "E:/Engine_V1/Draxion/Sandbox/Assets/Tileset/BasicTiles/Use/tileset.png";
	std::string m_Joe_Sprite_Full = "E:/Engine_V1/Draxion/Sandbox/Assets/Sprites/Joe_Walk.png";
	// TileMap
	std::string m_TileMap =
		"GGGGGGGGGGGGGGGG"
		"GGGGGWWWWWWWGGGG"
		"GGGGGGGGGGGGGGGG"
		"GGWWWWWGGGGGGGGG"
		"GGWWWWWGGGGGGGGG"
		"GGGGGGGGGGGGGGGG"
		"GGGGGGGGGGGGGGGG"
		"GGGGGGGGGGGGGGGG"
		"WWWWWWGGGGGGGGGG"
		"WWWWWWGGGGGGGGGW"
		"WWWWWWGGGGGGGGGW"
		"WWWWWWGGGGGGGGGW"
		"WWWWWWGGGGGGGGGG"
		"GGGGGGGGGGGGGGGG"
		"GGGGGGGGGGGGGGGG"
		"WWWWWWWGGGWWWWWW"
		"GGGGGGGGGGGGGGGG"
		"GGGGGGGGGGGGGGGG"
		"WWWWWGGGGGGGGGGG"
		"GGGGWGGGGGGGGGGG"
		"GGGGWGGGGGGGGGGG"
		"GGGGGGGGGGGGGGGG"
		"GGGGGGGGGGGWGGGG"
		"GGGWGGGGGGGGGGGG"
		"GGGGGGGGGGGGGGGG";
	Draxion::TileMap m_Map;
	Draxion::Player m_Player;
};