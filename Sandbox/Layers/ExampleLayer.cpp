#include "ExampleLayer.h"
#include "imgui/imgui.h"

namespace Draxion
{
	void ExampleLayer::OnAttach()
	{
		LOG_ENGINE_TRACE("Example Layer Attached");
		float vertices[]
		{
				// POS					// Color			  Tex-Coord
			-0.5f,-0.5f, 0.0f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f, // Bottom-Left  0
			-0.5f, 0.5f, 0.0f,		0.0f, 1.0f, 0.0f,		0.0f, 1.0f, // Top-Left     1
			 0.5f, 0.5f, 0.0f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f, // Top-Right    2
			 0.5f,-0.5f, 0.0f,		0.0f, 0.0f, 1.0f,		1.0f, 0.0f, // Bottom-Right 3
		};

		unsigned int indices[]
		{
			0,1,2,
			0,2,3,
		};
		
		//glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
		
		m_VAO.reset(VertexArray::Create());
		std::shared_ptr<VertexBuffer> m_VBO;
		m_VBO.reset(VertexBuffer::Create(vertices, sizeof(vertices) ));
		std::shared_ptr<IndexBuffer> m_EBO;
		m_EBO.reset(IndexBuffer::Create(indices, sizeof(indices)));


		m_VAO->Bind();
		//m_EBO->Bind();

	
		BufferLayout layout =
		{
			{ ShaderDataType::Float3, "aPos" },
			{ ShaderDataType::Float3, "aColor" },
			{ ShaderDataType::Float2, "aTexCoord" },
		};
		m_VBO->SetLayout(layout);


		m_VAO->AddVertexBuffers(m_VBO);
		m_VAO->SetIndexBuffer(m_EBO);

		m_Shader = new Shader("E:/Engine_V1/Draxion/Draxion/src/Draxion/Asset/OpenGL/Shaders/Basic.vert"
							 ,"E:/Engine_V1/Draxion/Draxion/src/Draxion/Asset/OpenGL/Shaders/Basic.frag");

		m_ShaderInv = new Shader("E:/Engine_V1/Draxion/Draxion/src/Draxion/Asset/OpenGL/Shaders/Basic.vert"
							 ,"E:/Engine_V1/Draxion/Draxion/src/Draxion/Asset/OpenGL/Shaders/Basicinverted.frag");
	

	}
	void ExampleLayer::OnDetach()
	{
		delete m_Shader;
		LOG_ENGINE_TRACE("Example Layer Detached");
	}

	void ExampleLayer::OnUpdate()
	{
		RenderCommand::SetClearColor({ 0.2f, 0.3f, 0.8f, 1.0f });
		RenderCommand::Clear();
		if(!IsHidden())
		{
			if( Draxion::Input::IsKeyPressed(DRX_KEY_0) )
			m_ShaderInv->Bind();
			else
			m_Shader->Bind();

			Renderer::BeginScene();
			RenderCommand::DrawIndexed(m_VAO);
			Renderer::EndScene();
		}
	}

	void ExampleLayer::OnImGuiRender()
	{
		ImGui::Begin("TestImGuiLayerInExample");
		ImGui::Text("Mic Test");
		ImGui::End();
	}

	void ExampleLayer::OnEvent(Event& e)
	{
		if (!IsHidden())
		{
			EventDispatcher d(e);

			d.Dispatch<KeyPressedEvent>([](KeyPressedEvent& e)
			{
				if ((e.GetKeyCode()) == DRX_KEY_LEFT_CONTROL)
				{
					return false;
				}
				return false;
			});
		}
	}
}
