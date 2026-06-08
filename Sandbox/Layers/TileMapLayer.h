#pragma once
#include "DraxionMain.h"
#include "Draxion/Renderer/TileMap/TileMap.h"

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
	std::string m_Grass_Full = "E:/Engine_V1/Draxion/Sandbox/Assets/Tileset/BasicTiles/Use/32_Grass-Water.png";
	// TileMap
	std::string m_TileMap =
		"GGGGGGG"
		"GWWWWWG"
		"GGWGGWG"
		"GGWGGWG"
		"GGWGGWG"
		"GWWWWWG"
		"GGGGGGG";
	Draxion::TileMap m_Map;
};