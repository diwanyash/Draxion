#include "TileMapLayer.h"
#include "ImGui/imgui.h"

TileMapLayer::TileMapLayer()
	:
	Layer("TileMapLayer")
{
}

void TileMapLayer::OnAttach()
{
	LOG_CLIENT_INFO( "TileMap Layer Attached");

	m_Map = Draxion::TileMap( m_TileMap, m_Grass_Full, { 7,7 }, { 4,4 }, { -3.0f,-3.0f,0.0f } );
	// m_Player = Draxion::Player(  );
	m_Camera_Con.SetZoomRatio(3.5f);

}

void TileMapLayer::OnDetach()
{
}

void TileMapLayer::OnUpdate(float dt)
{
	m_Camera_Con.OnUpdate( dt );
	// m_Player.OnUpdate( dt );

	Draxion::RenderCommand::SetClearColor({0.3f,0.7f,0.7f,1.0f});
	Draxion::RenderCommand::Clear();

	Draxion::Renderer2D::BeginScene( m_Camera_Con.GetCamera() );
	m_Map.Draw(dt);
	// m_Player.Draw(dt);
	Draxion::Renderer2D::EndScene();
}

void TileMapLayer::OnEvent(Draxion::Event& e)
{
	m_Camera_Con.OnEvent(e);
}

void TileMapLayer::OnImGuiRender()
{
	ImGui::Begin("Grid_Control");
	ImGuiIO& io = ImGui::GetIO();
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
	ImGui::Text("Zoom Level %.2f", m_Camera_Con.GetZoomRatio());
	ImGui::End();
}
