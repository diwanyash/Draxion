#pragma once
#include "DraxionMain.h"
#include "Draxion/Renderer/TileMap/TileMap.h"
#include "Draxion/Renderer/Sprite/Player.h"
#include "Draxion/Core/ECS/World.h"

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
	// ECS
	Draxion::World m_World;
	// Camera
	Draxion::OrthoGraphicCameraController m_Camera_Con = { 1280.0f / 720.0f };
	// Texture
	std::string m_Grass_Full = "E:/Engine_V1/Draxion/Sandbox/Assets/Tileset/BasicTiles/Use/tileset.png";
	std::string m_Joe_Sprite_Full = "E:/Engine_V1/Draxion/Sandbox/Assets/Sprites/Joe_Walk_Idle.png";
	Draxion::Ref<Draxion::Texture2D> m_Bush = nullptr;
	// TileMap
	std::string m_TileMap =
		"GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG"
		"GGGGGWWWWWWWGGGGGGGGGWWWWWWWGGGG"
		"GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG"
		"GGWWWWWGGGGGGGGGGGWWWWWGGGGGGGGG"
		"GGWWWWWGGGGGGGGGGGWWWWWGGGGGGGGG"
		"GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG"
		"GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG"
		"GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG"
		"WWWWWWGGGGGGGGGGWWWWWWGGGGGGGGGG"
		"WWWWWWGGGGGGGGGWWWWWWWGGGGGGGGGW"
		"WWWWWWGGGGGGGGGWWWWWWWGGGGGGGGGW"
		"WWWWWWGGGGGGGGGWWWWWWWGGGGGGGGGW"
		"WWWWWWGGGGGGGGGGWWWWWWGGGGGGGGGG"
		"GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG"
		"GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG"
		"WWWWWWWGGGWWWWWWWWWWWWWGGGWWWWWW"
		"GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG"
		"GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG"
		"WWWWWGGGGGGGGGGGWWWWWGGGGGGGGGGG"
		"GGGGWGGGGGGGGGGGGGGGWGGGGGGGGGGG"
		"GGGGWGGGGGGGGGGGGGGGWGGGGGGGGGGG"
		"GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG"
		"GGGGGGGGGGGWGGGGGGGGGGGGGGGWGGGG"
		"GGGWGGGGGGGGGGGGGGGWGGGGGGGGGGGG"
		"GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG";
	Draxion::TileMap m_Map;
	Draxion::Player m_Player;
};