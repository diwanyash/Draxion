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
	void HighLight( std::pair<int,int> GridLoc );
private:
	// Camera
	Draxion::OrthoGraphicCameraController m_Camera_Control = {1280.0f / 720.0f};

	// VBO
	Draxion::Ref<Draxion::VertexArray> m_VAO;

	// Shader
	Draxion::Ref<Draxion::Shader> m_TiledShader = nullptr;
	Draxion::Ref<Draxion::Shader> m_BasicColorShader = nullptr;

	// Texture
	Draxion::Ref<Draxion::Texture2D> m_Grass_Water = nullptr;

	// Vector/Value
	glm::ivec2 m_GridLoc = {1,1};
	glm::vec2 MouseCamPos;
	glm::ivec2 HoveredTile = {0,0};
	
	// Window
	int Win_Width = 1280;
	int Win_Height = 720;

	// Test
	std::vector<std::pair<int,int>> WorldGrid;
	glm::vec2 GridOffset = {0.0f,0.0f};
	glm::vec4 MapSize = {0.0f,0.0f,0.0f,0.0f};
	int GridSize_x = 50;
	int GridSize_y = 50;
	int GridSize   = 50;
};
