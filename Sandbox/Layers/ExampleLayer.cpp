#include "ExampleLayer.h"
#include "imgui/imgui.h"
#include <glm/gtc/type_ptr.hpp>



#include "src/Draxion/Platform/Windows/OpenGL/OpenGLShader.h"
namespace Draxion
{
	void ExampleLayer::OnAttach()
	{
		LOG_ENGINE_TRACE("Example Layer Attached");
		//		float vertices[]
		//		{
		//				// POS					// Color			  Tex-Coord
		//			-1.77f,-1.0f, 0.0f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f, // Bottom-Left  0
		//			-1.77f, 1.0f, 0.0f,		0.0f, 1.0f, 0.0f,		0.0f, 1.0f, // Top-Left     1
		//			 1.77f, 1.0f, 0.0f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f, // Top-Right    2
		//			 1.77f,-1.0f, 0.0f,		0.0f, 0.0f, 1.0f,		1.0f, 0.0f, // Bottom-Right 3
		//		};
		//		
		//		unsigned int indices[]
		//		{
		//			0,1,2,
		//			0,2,3,
		//		};
		//		
		//		//glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
		//		
		//		m_VAO = VertexArray::Create();
		//		
		//		Ref<VertexBuffer> m_VBO;
		//		m_VBO.reset(VertexBuffer::Create(vertices, sizeof(vertices) ));
		//		Ref<IndexBuffer> m_EBO;
		//		m_EBO.reset(IndexBuffer::Create(indices, sizeof(indices)));
		//		
		//		
		//		m_VAO->Bind();
		//		//m_EBO->Bind();
		//		
		//		
		//		BufferLayout layout =
		//		{
		//			{ ShaderDataType::Float3, "aPos" },
		//			{ ShaderDataType::Float3, "aColor" },
		//			{ ShaderDataType::Float2, "aTexCoord" },
		//		};
		//		m_VBO->SetLayout(layout);
		//		
		//		
		//		m_VAO->AddVertexBuffers(m_VBO);
		//		m_VAO->SetIndexBuffer(m_EBO);
		//		
		//		m_Shader = Shader::Create("E:/Engine_V1/Draxion/Draxion/src/Draxion/Asset/OpenGL/Shaders/Basic.vert"
		//							 ,"E:/Engine_V1/Draxion/Draxion/src/Draxion/Asset/OpenGL/Shaders/Basic.frag");
		//		
		//		m_Neduko_SanGoku = Texture2D::Create("E:/Engine_V1/Draxion/Draxion/src/Draxion/Asset/Images/Neduko.jpg");
		//		
		//		std::dynamic_pointer_cast<OpenGLShader>(m_Shader)->Bind();
		//		std::dynamic_pointer_cast<OpenGLShader>(m_Shader)->UploadUniformInt("u_Texture", 0);

		// std::dynamic_pointer_cast<OpenGLShader>(m_ShaderInv)->Bind();
		// std::dynamic_pointer_cast<OpenGLShader>(m_ShaderInv)->UploadUniformInt("u_Texture", 0);

		m_Neduko_SanGoku = Texture2D::Create("E:/Engine_V1/Draxion/Draxion/src/Draxion/Asset/Images/Neduko.jpg");

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
			//glm::vec3 pos = {0.0f,0.0f,0.0f};
			//glm::mat4 transform;
			//
			//Renderer::BeginScene( m_CameraController.GetCamera() );
			//m_Neduko_SanGoku->Bind();
			//transform = glm::translate(glm::mat4(1.0f), pos);
			//m_Neduko_SanGoku->Bind();
			
			Renderer2D::BeginScene( m_CameraController.GetCamera() );
			
			Renderer2D::DrawSquare(m_Neduko_SanGoku, { -1.0f,1.0f }, { 1.0f,1.0f }); // RED
			Renderer2D::DrawSquare(m_Neduko_SanGoku, { -1.0f,-1.0f,zR }, { 1.25f,1.25f }, {0.5f,1.0f,1.0f,0.1f}); // BLUE
			Renderer2D::DrawSquare({  1.0f,-1.0f }, { 1.75f,1.75f }, {0.2f,0.8f,0.3f,1.0f}); // BLUE
			Renderer2D::DrawSquare({  1.0f,1.0f }, { 1.25f,1.25f }, {1.0f,1.0f,0.0f,zB}); // BLUE
			
			Renderer2D::EndScene();
		}
	}

	void ExampleLayer::OnImGuiRender()
	{
		ImGui::Begin("TestImGuiLayerInExample");
		ImGuiIO& io = ImGui::GetIO();
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
		ImGui::Text("Zoom Ratio ( %.2f )", m_CameraController.GetZoomRatio());
		ImGui::SliderFloat("Z of RED", &zR, -0.5f,0.5f,"%.2f");
		ImGui::SliderFloat("Z of BLUE", &zB, -0.5f, 0.5f,"%.2f");
		//	ImGui::SliderFloat("Girl Alpha", &Occu, 0.0f,1.0f);
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
