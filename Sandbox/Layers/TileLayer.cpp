#include "TileLayer.h"
#include "imgui/imgui.h"
#include <glm/gtc/type_ptr.hpp>


TileLayer::TileLayer()
	:
	Layer("TileSet")
{
	WorldGrid.resize(GridSize_x * GridSize_y);
	MapSize = {0.0f, 0.0f, GridSize_x, GridSize_y};
	Regen();
}

void TileLayer::OnAttach()
{
	LOG_ENGINE_INFO("TileSet Layer Attached");
	float vertices[]
	{
			// POS					// Color			  Tex-Coord
		 0.0f, 0.0f, 0.0f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f, // Bottom-Left  0
		 0.0f, 1.0f, 0.0f,		0.0f, 1.0f, 0.0f,		0.0f, 1.0f, // Bottom-Right 1
		 1.0f, 1.0f, 0.0f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f, // Top-Right    2
		 1.0f, 0.0f, 0.0f,		0.0f, 0.0f, 1.0f,		1.0f, 0.0f, // Top-Left     3
	};

	unsigned int indices[]
	{
		0,3,1,
		1,3,2,
	};

	m_VAO.reset(Draxion::VertexArray::Create());
	
	Draxion::Ref<Draxion::VertexBuffer> t_VBO;
	t_VBO.reset(Draxion::VertexBuffer::Create(vertices, sizeof(vertices)));
	
	Draxion::Ref<Draxion::IndexBuffer> t_IBO;
	t_IBO.reset(Draxion::IndexBuffer::Create(indices, sizeof(indices)));
	
	m_VAO->Bind();

	Draxion::BufferLayout Layout =
	{
		{Draxion::ShaderDataType::Float3, "aPos"},
		{Draxion::ShaderDataType::Float3, "aColor"},
		{Draxion::ShaderDataType::Float2, "aTexCoord"}
	};
	t_VBO->SetLayout(Layout);

	m_VAO->AddVertexBuffers(t_VBO);
	m_VAO->SetIndexBuffer(t_IBO);

	m_TiledShader.reset( Draxion::Shader::Create("E:/Engine_V1/Draxion/Draxion/src/Draxion/Asset/OpenGL/Shaders/Tiled.vert"
		, "E:/Engine_V1/Draxion/Draxion/src/Draxion/Asset/OpenGL/Shaders/Tiled.frag"));

	m_BasicColorShader.reset( Draxion::Shader::Create("E:/Engine_V1/Draxion/Draxion/src/Draxion/Asset/OpenGL/Shaders/Tiled.vert"
		, "E:/Engine_V1/Draxion/Draxion/src/Draxion/Asset/OpenGL/Shaders/BasicColor.frag"));


	m_Grass_Water = Draxion::Texture2D::Create("E:/Engine_V1/Draxion/Sandbox/Assets/Tileset/BasicTiles/Use/32_Grass-Water.png");
	std::dynamic_pointer_cast<Draxion::OpenGLShader>(m_TiledShader)->Bind();
	std::dynamic_pointer_cast<Draxion::OpenGLShader>(m_TiledShader)->UploadUniformInt("u_Texture", 0);

}

void TileLayer::OnUpdate(float dt)
{
	m_Camera_Control.OnUpdate(dt);

	Draxion::RenderCommand::SetClearColor({0.2f,0.3f,0.3f,1.0f});
	Draxion::RenderCommand::Clear();

	Draxion::Renderer::BeginScene(m_Camera_Control.GetCamera());

	// Tramsforms
	glm::mat4 transform;


	////////////
	//std::dynamic_pointer_cast<Draxion::OpenGLShader>(m_TiledShader)->Bind();
	m_Grass_Water->Bind();

	// TRS transform
	std::dynamic_pointer_cast<Draxion::OpenGLShader>(m_TiledShader)->Bind();
	for(int y = 0; y < GridSize_y; y++)
	{
		for(int x = 0; x < GridSize_x; x++)
		{
			transform = 
				glm::translate(glm::mat4(1.0f), glm::vec3(GridOffset.x + float(x), GridOffset.y + float(y), 0.0f)) // * Rotation
				* glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));

			auto pair = WorldGrid[GridSize * y + x];
			int grid_x = pair.first;
			int grid_y = pair.second;

			std::dynamic_pointer_cast<Draxion::OpenGLShader>(m_TiledShader)->UploadUniformInt2("u_Grid", glm::ivec2(grid_x, grid_y));
			Draxion::Renderer::Submit(m_TiledShader, m_VAO, transform);
		}
	}

	HoveredTile.x = std::floor(MouseCamPos.x);
	HoveredTile.y = std::floor(MouseCamPos.y);

	transform =
		glm::translate(glm::mat4(1.0f), glm::vec3(HoveredTile,0.0f));

	std::dynamic_pointer_cast<Draxion::OpenGLShader>(m_BasicColorShader)->Bind();
	std::dynamic_pointer_cast<Draxion::OpenGLShader>(m_BasicColorShader)->UploadUniformFloat4("u_Color", {1.0f,1.0f,1.0f,0.3f});
	Draxion::Renderer::Submit(m_BasicColorShader, m_VAO, transform);


	Draxion::Renderer::EndScene();;
}

void TileLayer::OnImGuiRender()
{
	ImGui::Begin("Grid_Control");
	ImGuiIO& io = ImGui::GetIO();
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
	ImGui::Text("Grid Control XY");
	ImGui::SliderInt2("Grid(XY)", glm::value_ptr(m_GridLoc),0,3);
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

	//LOG_CLIENT_TRACE("CAM (X,Y) = (" << m_Camera_Control.GetPos().x << "," << m_Camera_Control.GetPos().y << ")");
	d.Dispatch<Draxion::MouseMovedEvent>([&](Draxion::MouseMovedEvent& e)
	{
		glm::vec2 MousePos = { 2.0f * (float)e.GetXpos() / (float)Win_Width - 1.0f , 1.0f - (2.0f * (float)e.GetYpos() / (float)Win_Height) };

		MouseCamPos.x = MousePos.x * m_Camera_Control.GetAspectRatio()
			* m_Camera_Control.GetZoomRatio()
			+ m_Camera_Control.GetPos().x;

		MouseCamPos.y = MousePos.y * m_Camera_Control.GetZoomRatio() + m_Camera_Control.GetPos().y;


		return false;
	});

}

void TileLayer::Regen()
{
	for (int y = 0; y < GridSize_y; y++)
	{
		for (int x = 0; x < GridSize_x; x++)
		{
			WorldGrid[GridSize * y + x] = { Draxion::RandomGen::Get<int>(0, 3),Draxion::RandomGen::Get<int>(0, 3) };
		}
	}
}