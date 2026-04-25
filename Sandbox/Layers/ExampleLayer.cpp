#include "ExampleLayer.h"

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
		
		m_VAO = new VertexArray();
		m_VBO = new VertexBuffer( vertices, sizeof(vertices) );
		m_EBO = new IndexBuffer( indices, 6 );

		m_VAO->Bind();
		m_EBO->Bind();

		m_VAO->AddBuffer(*m_VBO);

		m_Shader = new Shader("E:/Engine_V1/Draxion/Draxion/src/Draxion/Asset/OpenGL/Shaders/Basic.vs"
							 ,"E:/Engine_V1/Draxion/Draxion/src/Draxion/Asset/OpenGL/Shaders/Basic.fs");
	

	}
	void ExampleLayer::OnDetach()
	{
		delete m_VAO;
		delete m_VBO;
		delete m_EBO;
		delete m_Shader;
		LOG_ENGINE_TRACE("Example Layer Detached");
	}

	void ExampleLayer::OnUpdate()
	{
		m_Shader->Bind();
		RendererCommand::DrawIndexed( *m_VAO, 6 );
	}

	void ExampleLayer::OnEvent(Event& e)
	{
		//LOG_ENGINE_TRACE( e.GetName() );
		EventDispatcher d(e);

		d.Dispatch<KeyPressedEvent>([](KeyPressedEvent& e)
		{
			if ((e.GetKeyCode()) == Draxion::Key::VK_CONTROL)
			{
				RendererCommand::PrimitiveChange();
				LOG_CLIENT_TRACE("Drawing Polygon Changed");
				return true;
			}
			return false;
		});
	}
}
