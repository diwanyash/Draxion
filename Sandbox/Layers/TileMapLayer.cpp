#include "TileMapLayer.h"
#include "ImGui/imgui.h"

TileMapLayer::TileMapLayer()
	:
	Layer("TileMapLayer")
{
	DX_PROFILE_FUNCTION();
}

void TileMapLayer::OnAttach()
{
	DX_PROFILE_FUNCTION();

	LOG_CLIENT_INFO("TileMap Layer Attached");

	for (int i = 0; i < 5; i++)
	{
		Draxion::Entity Bush = m_World.CreateEntity();
		m_World.AddComponent<Draxion::TransformComponent>(Bush);
		m_World.AddComponent<Draxion::SpriteComponent>(Bush);
		
		auto& transform = m_World.GetComponent<Draxion::TransformComponent>(Bush);
		transform.Position.z = 0.4f;
		transform.Position.x = i * 2.0f;

		auto& sprite = m_World.GetComponent<Draxion::SpriteComponent>(Bush);
		sprite.Texture = Draxion::Texture2D::Create("E:/Engine_V1/Draxion/Sandbox/Assets/Sprites/Bush.png");
	}
	m_Map = Draxion::TileMap( m_TileMap, m_Grass_Full, { 32,25 }, { 4,4 }, { -3.0f,-3.0f,0.0f } );
	m_Player = Draxion::Player(m_Joe_Sprite_Full, {1.0f,1.0f,1.0f});
	m_Camera_Con.SetZoomRatio(3.5f);

}

void TileMapLayer::OnDetach()
{
	DX_PROFILE_FUNCTION();

}

void TileMapLayer::OnUpdate(float dt)
{
	DX_PROFILE_FUNCTION();

	Draxion::Renderer2D::ResetStates();

	{
		DX_PROFILE_SCOPE("TileMap Calculate");
		m_Camera_Con.OnUpdateOnly();
		m_Player.OnUpdate(dt);
		auto i = m_Player.GetPos() - glm::vec3{ -0.5f, -0.5f, 0.0f };
		m_Camera_Con.SetPos({ i.x,i.y,0.0f });
	}

	Draxion::RenderCommand::SetClearColor({0.3f,0.7f,0.7f,1.0f});
	Draxion::RenderCommand::Clear();

	Draxion::Renderer2D::BeginScene( m_Camera_Con.GetCamera() );
	{
		DX_PROFILE_SCOPE("TileMap Draw");

		m_Map.Draw(dt);
		m_Player.Draw(dt);

		auto& entities = m_World.GetEntities();
		for(auto& entity : entities)
		{
			if (!m_World.HasComponent<Draxion::TransformComponent>(entity))
				continue;
			if (!m_World.HasComponent<Draxion::SpriteComponent>(entity))
				continue;

			auto& transform = m_World.GetComponent<Draxion::TransformComponent>(entity);
			auto& sprite = m_World.GetComponent<Draxion::SpriteComponent>(entity);

			Draxion::Renderer2D::DrawSquare(sprite.Texture, transform.Position, transform.Scale);
		}
	}
	Draxion::Renderer2D::EndScene();
}

void TileMapLayer::OnEvent(Draxion::Event& e)
{
	m_Camera_Con.OnEvent(e);
}

void TileMapLayer::OnImGuiRender()
{
	DX_PROFILE_FUNCTION();

	static float FrameTimes[1000] = {};
	static int Offset = 0;

	ImGui::SetNextWindowBgAlpha(0.35f);
	ImGui::Begin("Grid_Control");
	ImGuiIO& io = ImGui::GetIO();
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
	ImGui::Text("Zoom Level %.2f", m_Camera_Con.GetZoomRatio());
	ImGui::Text("Draw Calls %d", Draxion::Renderer2D::GetStates().DrawCalls);
	ImGui::Text("Square Count %d", Draxion::Renderer2D::GetStates().SquareCount);
	ImGui::End();
}
