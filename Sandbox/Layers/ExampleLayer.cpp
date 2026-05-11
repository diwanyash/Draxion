#include "ExampleLayer.h"
#include "imgui/imgui.h"

namespace Draxion
{
	void ExampleLayer::OnAttach()
	{
		m_Camera.SetPosition({0.0f,0.0f,0.0f});

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

		m_Shader = std::make_shared<Shader>("E:/Engine_V1/Draxion/Draxion/src/Draxion/Asset/OpenGL/Shaders/Basic.vert"
							 ,"E:/Engine_V1/Draxion/Draxion/src/Draxion/Asset/OpenGL/Shaders/Basic.frag");

		m_ShaderInv = std::make_shared<Shader>("E:/Engine_V1/Draxion/Draxion/src/Draxion/Asset/OpenGL/Shaders/Basic.vert"
							 ,"E:/Engine_V1/Draxion/Draxion/src/Draxion/Asset/OpenGL/Shaders/Basicinverted.frag");
	

	}
	void ExampleLayer::OnDetach()
	{
		LOG_ENGINE_TRACE("Example Layer Detached");
	}

	void ExampleLayer::OnUpdate()
	{
		RenderCommand::SetClearColor({ 0.2f, 0.3f, 0.8f, 1.0f });
		RenderCommand::Clear();
		if(!IsHidden())
		{

			if ( Draxion::Input::IsKeyPressed( DRX_KEY_W ) )
			{
				m_Camera.SetPosition(Cam_Pos += glm::vec3{0.0f,0.01f,0.0f});
			}
			if (Draxion::Input::IsKeyPressed(DRX_KEY_S))
			{
				m_Camera.SetPosition(Cam_Pos += glm::vec3{ 0.0f,-0.01f,0.0f });
			}
			if( Draxion::Input::IsKeyPressed(DRX_KEY_A) )
			{
				m_Camera.SetPosition(Cam_Pos += glm::vec3{-0.01f,0.0f,0.0f});
			}
			if( Draxion::Input::IsKeyPressed(DRX_KEY_D) )
			{
				m_Camera.SetPosition(Cam_Pos += glm::vec3{0.01f,0.0f,0.0f});
			}
			if( Draxion::Input::IsKeyPressed(DRX_KEY_Q) )
			{
				m_Camera.SetRotation( m_Camera.GetRotation() + 1.0f );
			}
			if( Draxion::Input::IsKeyPressed(DRX_KEY_E) )
			{
				m_Camera.SetRotation( m_Camera.GetRotation() - 1.0f );
			}
			if( Draxion::Input::IsKeyPressed(DRX_KEY_Z) )
			{
				m_Camera.SetPosition(Cam_Pos += glm::vec3{ 0.0f,0.0f,1.0f });
			}
			if( Draxion::Input::IsKeyPressed(DRX_KEY_X) )
			{
				m_Camera.SetPosition(Cam_Pos += glm::vec3{ 0.0f,0.0f,-1.0f });
			}

			Renderer::BeginScene( m_Camera );
			//RenderCommand::DrawIndexed(m_VAO);
			if (Draxion::Input::IsKeyPressed(DRX_KEY_0))
			{
				Renderer::Submit(m_ShaderInv, m_VAO);
			}
			else
			{
				Renderer::Submit(m_Shader, m_VAO);
			}
			
			Renderer::EndScene();
		}
	}

	void ExampleLayer::OnImGuiRender()
	{
		ImGui::Begin("TestImGuiLayerInExample");
		ImGuiIO& io = ImGui::GetIO();
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
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
