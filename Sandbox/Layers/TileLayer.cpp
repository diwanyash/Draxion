#include "TileLayer.h"
#include "imgui/imgui.h"
#include <glm/gtc/type_ptr.hpp>

TileLayer::TileLayer()
	:
	Layer("TileSet")
{
	DisplayGridMap.resize((GridSize_x - 1) * (GridSize_y - 1));
	MapSize = {0.0f, 0.0f, GridSize_x, GridSize_y};
}

void TileLayer::OnAttach()
{
	LOG_ENGINE_INFO("TileSet Layer Attached");

	m_Grass_Full = Draxion::Texture2D::Create("E:/Engine_V1/Draxion/Sandbox/Assets/Tileset/BasicTiles/Use/32_Grass-Water.png");
	
	for (int y = 0; y < Gridy; y++)
	{
		for (int x = 0; x < Gridx; x++)
			GridVec.emplace_back( std::make_shared<TileMap>(x,y) );
	}

	for (int y = 0; y < GridSize_y; y++)
	{
		for (int x = 0; x < GridSize_x; x++)
			WorldGridMap.emplace_back(std::make_shared<WorldGrid>(WorldGrid::TileType::Grass));
		//	Draxion::RandomGen::Get<int>(0, 1) ? std::make_shared<WorldGrid>(WorldGrid::TileType::Water) :
		//	std::make_shared<WorldGrid>(WorldGrid::TileType::Grass) );
	}

	Regen();
	m_Camera_Control.SetZoomRatio(5.0f);
}

void TileLayer::OnUpdate(float dt)
{
	m_Camera_Control.OnUpdate(dt);

	Draxion::RenderCommand::SetClearColor({ 0.2f,0.3f,0.3f,1.0f });
	Draxion::RenderCommand::Clear();

	Draxion::Renderer2D::BeginScene(m_Camera_Control.GetCamera());


	/////////////////////////////////////////////////
	//////Input//////////////////////////////////////
	/////////////////////////////////////////////////

	std::pair<int, int> CurMousePos = Draxion::Input::GetMousePosition();

	glm::vec2 MousePos = { 2.0f * (float)CurMousePos.first / (float)Win_Width - 1.0f ,
		1.0f - (2.0f * (float)CurMousePos.second / (float)Win_Height) };

	MouseCamPos.x = MousePos.x * m_Camera_Control.GetAspectRatio()
		* m_Camera_Control.GetZoomRatio()
		+ m_Camera_Control.GetPos().x;

	MouseCamPos.y = MousePos.y * m_Camera_Control.GetZoomRatio() + m_Camera_Control.GetPos().y;
	HoveredTile = glm::ivec2{ std::floor(MouseCamPos.x + 0.5f), std::floor(MouseCamPos.y + 0.5f) }; // +0.5f

	/////////////////////////////////////////////////
	/////////////////////////////////////////////////
	/////////////////////////////////////////////////

	// TRS transform
	for (int y = 0; y < GridSize_y - 1; y++)
	{
		for (int x = 0; x < GridSize_x - 1; x++)
		{
			auto pair = DisplayGridMap[(GridSize - 1) * y + x];
			int grid_x = pair.first;
			int grid_y = pair.second;

			// std::dynamic_pointer_cast<Draxion::OpenGLShader>(m_TiledShader)->UploadUniformInt2("u_Grid", glm::ivec2(grid_x, grid_y));
			//		Draxion::Renderer2D::SetGrid({ grid_x,grid_y });
			/*
				Make Array of gridx before sending it to shader/ this thing wont work on batch rendering
				as all data are sent once
			Draxion::Renderer2D::DrawSquare(m_Grass_BSlash, , {1.0f,1.0f});
			*/
			Draxion::Renderer2D::DrawSquare(m_Grass_Full, {float(x),float(y),0.0f },
				GridVec[grid_y * 4 + grid_x]->GetUVPos(), { 1.0f,1.0f });
		}
	}

	// Draxion::DrawTileMap(m_TileTexture,/*in string format*/ Map, /*Tiles per Tileset*/{4, 4},/*Pos*/{0.0f,0.0f,0.0f});

	//	Draxion::Renderer2D::DrawSquare(m_Grass_Full, { 0.0f,0.0f },GridVec[6]->GetUVPos(), {1.0f,1.0f});

	// Draxion::Renderer2D::DrawSquare(m_Grass_BSlash, { -1.0f,-1.0f }, { 1.0f,1.0f });

	if (Draxion::Input::IsMouseButtonPressed(DRX_MOUSE_BUTTON_LEFT))
	{
		int x = HoveredTile.x;
		int y = HoveredTile.y;
		if( x >= 0 && y >= 0 && x < GridSize_x && y < GridSize_y)
		{
			WorldGridMap[y * GridSize_x + x]->SetType(WorldGrid::TileType::Water);
		}
		RegenWorldGrid();
	}
	if (Draxion::Input::IsMouseButtonPressed(DRX_MOUSE_BUTTON_RIGHT))
	{
		int x = HoveredTile.x;
		int y = HoveredTile.y;
		if (x >= 0 && y >= 0)
		{
			WorldGridMap[y * GridSize_x + x]->SetType(WorldGrid::TileType::Grass);
		}
		RegenWorldGrid();
	}
		Draxion::Renderer2D::DrawSquare({ ((float)HoveredTile.x - 0.5f), (float)HoveredTile.y - 0.5f,0.1f }, { 1.0f,1.0f }, { 1.0f,1.0f,1.0f,0.3f }); // -0.5f
		Draxion::Renderer2D::EndScene();;
}
void TileLayer::OnImGuiRender()
{
	ImGui::Begin("Grid_Control");
	ImGuiIO& io = ImGui::GetIO();
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
	ImGui::Text("Hov (%d,%d) ", HoveredTile.x, HoveredTile.y);
	// ImGui::Text("UVpos (%.2f)", glm::value_ptr(GridVec[std::abs(HoveredTile.y) * GridSize_y + std::abs(HoveredTile.x)]->GetUVPos()));
	if (ImGui::Button("RegenerateGrid"))
	{
		Regen();
	}
	ImGui::End();
}

void TileLayer::OnEvent(Draxion::Event& e)
{
	Draxion::EventDispatcher d(e);
	m_Camera_Control.OnEvent(e);

	d.Dispatch<Draxion::WindowsResizeEvent>([&](Draxion::WindowsResizeEvent& e)
	{
		Win_Width = e.GetWidth();
		Win_Height = e.GetHeight();
		return false;
	});

	d.Dispatch<Draxion::MouseButtonPressed>([&](Draxion::MouseButtonPressed& e)
	{
		int a = 0;
		return false;
	});
}

void TileLayer::Regen()
{
	for (int y = 0; y < GridSize_y; y++)
	{
		for (int x = 0; x < GridSize_x; x++)
			WorldGridMap[y * GridSize_x + x]->SetType(WorldGrid::TileType::Grass);
		//	Draxion::RandomGen::Get<int>(0, 1) ? std::make_shared<WorldGrid>(WorldGrid::TileType::Water) :
		//	std::make_shared<WorldGrid>(WorldGrid::TileType::Grass) );
	}
	for (int y = 0; y < GridSize_y - 1; y++)
	{
		for (int x = 0; x < GridSize_x - 1; x++)
		{
			DisplayGridMap[(GridSize - 1) * y + x] = { 2,2 };//{ Draxion::RandomGen::Get<int>(0, 3),Draxion::RandomGen::Get<int>(0, 3) };
		}
	}
}

void TileLayer::RegenWorldGrid()
{
	for ( int y = 0; y < GridSize_y - 1; y++)
	{
		for (int x = 0; x < GridSize_x - 1; x++)
		{
			DisplayGridMap[y * (GridSize_x - 1) +x] = SetDisplayGrid(x, y);
		}
	}
}



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


std::pair<int, int> TileLayer::SetDisplayGrid( int x, int y )
{
	WorldGrid::TileType BL = WorldGridMap[y       * GridSize_x +  x]->GetType();
	WorldGrid::TileType TL = WorldGridMap[(y + 1) * GridSize_x +  x]->GetType();
	WorldGrid::TileType TR = WorldGridMap[(y + 1) * GridSize_x + (x + 1)]->GetType();
	WorldGrid::TileType BR = WorldGridMap[y       * GridSize_x + (x + 1)]->GetType();

	uint8_t mask = 0;

	if (BL == WorldGrid::TileType::Grass)
		mask |= (1 << 3);

	if (TL == WorldGrid::TileType::Grass)
		mask |= (1 << 2);

	if (TR == WorldGrid::TileType::Grass)
		mask |= (1 << 1);

	if (BR == WorldGrid::TileType::Grass)
		mask |= (1 << 0);

	return TileLookup[mask];
}

std::pair<int, int> TileLayer::GetVector(WorldGrid::TileType BL, WorldGrid::TileType TL, WorldGrid::TileType TR, WorldGrid::TileType BR)
{
	uint8_t mask = 0;
	
	if (BL == WorldGrid::TileType::Grass)
		mask |= (1 << 3);
	
	if (TL == WorldGrid::TileType::Grass)
		mask |= (1 << 2);
	
	if (TR == WorldGrid::TileType::Grass)
		mask |= (1 << 1);
	
	if (BR == WorldGrid::TileType::Grass)
		mask |= (1 << 0);

	return TileLookup[mask];
}





