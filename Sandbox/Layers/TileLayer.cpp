#include "TileLayer.h"
#include "imgui/imgui.h"
#include <glm/gtc/type_ptr.hpp>


#include "src/Draxion/Platform/Windows/OpenGL/OpenGLShader.h"

TileLayer::TileLayer()
	:
	Layer("TileSet")
{
	DisplayGridMap.resize((GridSize_x - 1) * (GridSize_y - 1));
	MapSize = {0.0f, 0.0f, GridSize_x, GridSize_y};
	Regen();
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
			WorldGridMap.emplace_back( std::make_shared<WorldGrid>(WorldGrid::TileType::Grass) );
	}

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
			Draxion::Renderer2D::DrawSquare(m_Grass_Full, { GridOffset.x + float(x), GridOffset.y + float(y),0.0f },
				GridVec[grid_y * 4 + grid_x]->GetUVPos(), { 1.0f,1.0f });
		}
	}

	//	Draxion::Renderer2D::DrawSquare(m_Grass_Full, { 0.0f,0.0f },GridVec[6]->GetUVPos(), {1.0f,1.0f});

	// Draxion::Renderer2D::DrawSquare(m_Grass_BSlash, { -1.0f,-1.0f }, { 1.0f,1.0f });

	if (Draxion::Input::IsMouseButtonPressed(DRX_MOUSE_BUTTON_LEFT))
	{
		int x = HoveredTile.x;
		int y = HoveredTile.y;
		if( x >= 0 && y >= 0)
		{
			WorldGridMap[y * GridSize_y + x]->SetType(WorldGrid::TileType::Water);
		}
		RegenWorldGrid();
	}
	if (Draxion::Input::IsMouseButtonPressed(DRX_MOUSE_BUTTON_RIGHT))
	{
		int x = HoveredTile.x;
		int y = HoveredTile.y;
		if (x >= 0 && y >= 0)
		{
			WorldGridMap[y * GridSize_y + x]->SetType(WorldGrid::TileType::Grass);
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
	for (int y = 0; y < GridSize_y - 1; y++)
	{
		for (int x = 0; x < GridSize_x - 1; x++)
		{
			DisplayGridMap[(GridSize - 1) * y + x] = { Draxion::RandomGen::Get<int>(0, 3),Draxion::RandomGen::Get<int>(0, 3) };
		}
	}
}

void TileLayer::RegenWorldGrid()
{
	for ( int y = 0; y < GridSize_y - 1; y++)
	{
		for (int x = 0; x < GridSize_x - 1; x++)
		{
			DisplayGridMap[y * (GridSize_y - 1) +x] = SetDisplayGrid(x, y);
		}
	}
}

std::pair<int, int> TileLayer::SetDisplayGrid( int x, int y )
{
	WorldGrid::TileType BL = WorldGridMap[y       * GridSize_y +  x]->GetType();
	WorldGrid::TileType TL = WorldGridMap[(y + 1) * GridSize_y +  x]->GetType();
	WorldGrid::TileType TR = WorldGridMap[(y + 1) * GridSize_y + (x + 1)]->GetType();
	WorldGrid::TileType BR = WorldGridMap[y       * GridSize_y + (x + 1)]->GetType();



	return GetVector(BL,TL,TR,BR);;
}

enum Tile4
{
	WWWW,
	WWWG,
	GWGW,
	WGWW,
	WWGW,
	WGGW,
	WGGG,
	GGWW,
	WGWG,
	GWGG,
	GGGG,
	GGGW,
	GWWW,
	WWGG,
	GGWG,
	GWWG
};

std::pair<int, int> TileLayer::GetVector(WorldGrid::TileType BL, WorldGrid::TileType TL, WorldGrid::TileType TR, WorldGrid::TileType BR)
{
	if ( BL == WorldGrid::TileType::Water &&
		 TL == WorldGrid::TileType::Water && 
		 TR == WorldGrid::TileType::Water && 
		 BR == WorldGrid::TileType::Water)
	{
		return {0,0};
	}
	else if (BL == WorldGrid::TileType::Water &&
			 TL == WorldGrid::TileType::Water &&
			 TR == WorldGrid::TileType::Water &&
			 BR == WorldGrid::TileType::Grass)
	{
		return { 1,0 };
	}
	else if (BL == WorldGrid::TileType::Grass &&
			 TL == WorldGrid::TileType::Water &&
			 TR == WorldGrid::TileType::Grass &&
			 BR == WorldGrid::TileType::Water)
	{
		return { 2,0 };
	}
	else if (BL == WorldGrid::TileType::Water &&
			 TL == WorldGrid::TileType::Grass &&
			 TR == WorldGrid::TileType::Water &&
			 BR == WorldGrid::TileType::Water)
	{
		return { 3,0 };
	}
	else if (BL == WorldGrid::TileType::Water &&
			 TL == WorldGrid::TileType::Water &&
			 TR == WorldGrid::TileType::Grass &&
			 BR == WorldGrid::TileType::Water)
	{
		return { 0,1 };
	}
	else if (BL == WorldGrid::TileType::Water &&
			 TL == WorldGrid::TileType::Grass &&
			 TR == WorldGrid::TileType::Grass &&
			 BR == WorldGrid::TileType::Water)
	{
		return { 1,1 };
	}
	else if (BL == WorldGrid::TileType::Water &&
			 TL == WorldGrid::TileType::Grass &&
			 TR == WorldGrid::TileType::Grass &&
			 BR == WorldGrid::TileType::Grass)
	{
		return { 2,1 };
	}
	else if (BL == WorldGrid::TileType::Grass &&
			 TL == WorldGrid::TileType::Grass &&
			 TR == WorldGrid::TileType::Water &&
			 BR == WorldGrid::TileType::Water)
	{
		return { 3,1 };
	}
	else if (BL == WorldGrid::TileType::Water &&
			 TL == WorldGrid::TileType::Grass &&
			 TR == WorldGrid::TileType::Water &&
			 BR == WorldGrid::TileType::Grass)
	{
		return { 0,2 };
	}
	else if (BL == WorldGrid::TileType::Grass &&
			 TL == WorldGrid::TileType::Water &&
			 TR == WorldGrid::TileType::Grass &&
			 BR == WorldGrid::TileType::Grass)
	{
		return { 1,2 };
	}
	else if (BL == WorldGrid::TileType::Grass &&
			 TL == WorldGrid::TileType::Grass &&
			 TR == WorldGrid::TileType::Grass &&
			 BR == WorldGrid::TileType::Grass)
	{
		return { 2,2 };
	}
	else if (BL == WorldGrid::TileType::Grass &&
			 TL == WorldGrid::TileType::Grass &&
			 TR == WorldGrid::TileType::Grass &&
			 BR == WorldGrid::TileType::Water)
	{
		return { 3,2 };
	}
	else if (BL == WorldGrid::TileType::Grass &&
			 TL == WorldGrid::TileType::Water &&
			 TR == WorldGrid::TileType::Water &&
			 BR == WorldGrid::TileType::Water)
	{
		return { 0,3 };
	}
	else if (BL == WorldGrid::TileType::Water &&
			 TL == WorldGrid::TileType::Water &&
			 TR == WorldGrid::TileType::Grass &&
			 BR == WorldGrid::TileType::Grass)
	{
		return { 1,3 };
	}
	else if (BL == WorldGrid::TileType::Grass &&
			 TL == WorldGrid::TileType::Grass &&
			 TR == WorldGrid::TileType::Water &&
			 BR == WorldGrid::TileType::Grass)
	{
		return { 2,3 };
	}
	else if (BL == WorldGrid::TileType::Grass &&
			 TL == WorldGrid::TileType::Water &&
			 TR == WorldGrid::TileType::Water &&
			 BR == WorldGrid::TileType::Grass)
	{
		return { 3,3 };
	}
	else
	{
		return { 0,0 };
	}

	LOG_CLIENT_ERROR("Invalid Return Type in GetVector");
	return std::pair<int, int>();
}




