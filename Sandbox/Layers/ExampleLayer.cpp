#include "ExampleLayer.h"
#include "imgui/imgui.h"
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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
		Ref<VertexBuffer> m_VBO;
		m_VBO.reset(VertexBuffer::Create(vertices, sizeof(vertices) ));
		Ref<IndexBuffer> m_EBO;
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

		m_Shader.reset(Shader::Create("E:/Engine_V1/Draxion/Draxion/src/Draxion/Asset/OpenGL/Shaders/Basic.vert"
							 ,"E:/Engine_V1/Draxion/Draxion/src/Draxion/Asset/OpenGL/Shaders/Basic.frag"));

		m_ShaderInv.reset(Shader::Create("E:/Engine_V1/Draxion/Draxion/src/Draxion/Asset/OpenGL/Shaders/Basic.vert"
							 ,"E:/Engine_V1/Draxion/Draxion/src/Draxion/Asset/OpenGL/Shaders/Basicinverted.frag"));
	
		m_Neduko_SanGoku = Texture2D::Create("../Draxion/src/Draxion/Asset/Images/Neduko.jpg");
		m_Pikachuuu = Texture2D::Create("../Draxion/src/Draxion/Asset/Images/Girl.png");

		std::dynamic_pointer_cast<OpenGLShader>(m_Shader)->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(m_Shader)->UploadUniformInt("u_Texture", 0);

		std::dynamic_pointer_cast<OpenGLShader>(m_ShaderInv)->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(m_ShaderInv)->UploadUniformInt("u_Texture", 0);

	}
	void ExampleLayer::OnDetach()
	{
		LOG_ENGINE_TRACE("Example Layer Detached");
	}

	void ExampleLayer::OnUpdate(float dt)
	{
		m_CameraController.OnUpdate(dt);

		RenderCommand::SetClearColor({ 0.2f, 0.3f, 0.8f, 1.0f });
		RenderCommand::Clear();
		if(!IsHidden())
		{			
			glm::vec3 pos = {0.0f,0.0f,0.0f};
			glm::vec3 pos2 = {0.25f,0.25f,0.0f};
			glm::mat4 transform;

			Renderer::BeginScene( m_CameraController.GetCamera() );
			
			m_Neduko_SanGoku->Bind();

			if (Draxion::Input::IsKeyPressed(DRX_KEY_0))
			{
				transform = glm::translate(glm::mat4(1.0f), pos);
				Renderer::Submit(m_ShaderInv, m_VAO, transform);
			}
			else
			{
				transform = glm::translate(glm::mat4(1.0f), pos);
				Renderer::Submit(m_Shader, m_VAO, transform);
			}

			m_Pikachuuu->Bind();
			transform = glm::translate(glm::mat4(1.0f), pos2);
			Renderer::Submit(m_Shader, m_VAO, transform);

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
			m_CameraController.OnEvent(e);

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
