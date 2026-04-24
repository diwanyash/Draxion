#include "ExampleLayer.h"
#include <string>

namespace Draxion
{
	void ExampleLayer::OnAttach()
	{
		LOG_ENGINE_TRACE("Example Layer Attached");
		float vertices[]
		{
			-0.5f,-0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // 0
			0.0f , 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // 1
			0.5f ,-0.5f, 0.0f, 0.0f, 0.0f, 1.0f, // 2
		};

		unsigned int indices[]
		{
			0,1,2,
		};
		
		//glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
		
		m_VAO = new VertexArray();
		m_VBO = new VertexBuffer( vertices, sizeof(vertices) );
		m_EBO = new IndexBuffer( indices, 3 );

		m_VAO->Bind();
		m_EBO->Bind();

		m_VAO->AddBuffer(*m_VBO);

		std::string vs =
			"#version 330 core\n"
			"\n"
			"layout (location = 0) in vec3 aPos;\n"
			"layout (location = 1) in vec3 aColor;\n"
			"\n"
			"out vec3 OurColor;\n"
			"\n"
			"void main()\n"
			"{\n"
			"	gl_Position = vec4(aPos.xyz, 1.0);\n"
			"	OurColor = aColor;\n"
			"}\n";

		std::string fs =
			"#version 330 core\n"
			"\n"
			"in vec3 OurColor;\n"
			"out vec4 FragOut;\n"
			"\n"
			"void main()\n"
			"{\n"
			"	FragOut = vec4(OurColor, 1.0f);\n"
			"}\n";
			

		m_Shader = new Shader(vs,fs);

	}
	void ExampleLayer::OnDetach()
	{
		LOG_ENGINE_TRACE("Example Layer Detached");
	}

	void ExampleLayer::OnUpdate()
	{
		m_Shader->Bind();
		RendererCommand::DrawIndexed( *m_VAO, 3 );
	}

	void ExampleLayer::OnEvent(Event& e)
	{
		//LOG_ENGINE_TRACE( e.GetName() );
		EventDispatcher d(e);

		d.Dispatch<KeyPressedEvent>([](KeyPressedEvent& e)
		{
			if ((e.GetKeyCode()) == Draxion::Key::A)
			{
				LOG_CLIENT_TRACE("Keyboard Event \"A\" Handled by ExampleLayer");
				return true;
			}
			return false;
		});
	}
}
