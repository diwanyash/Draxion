#include "Core.h"
#include "Renderer2D.h"
#include <glm/ext/matrix_transform.hpp>
#include "Draxion/Renderer/Buffer/VertexArray.h"
#include "Draxion/Renderer/Shader/Shader.h"
#include "Draxion/Renderer/RendererCommand.h"


#include "Draxion/Platform/Windows/OpenGL/OpenGLShader.h"

namespace Draxion
{
	struct Renderer2DStorage
	{
		Ref<VertexArray> SquareVertexArray;
		Ref<Texture2D> WhiteTexture;
		Ref<Shader> Shader;
	};

	static Renderer2DStorage* s_Data;
	
	void Renderer2D::Init()
	{
		s_Data = new Renderer2DStorage();
		
		s_Data->WhiteTexture = Texture2D::Create("E:/Engine_V1/Draxion/Draxion/src/Draxion/Asset/Images/WhitePixel.png");

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

		//glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

		s_Data->SquareVertexArray = VertexArray::Create();

		Ref<VertexBuffer> m_VBO;
		m_VBO.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		Ref<IndexBuffer> m_EBO;
		m_EBO.reset(IndexBuffer::Create(indices, sizeof(indices)));


		s_Data->SquareVertexArray->Bind();
		//m_EBO->Bind();


		BufferLayout layout =
		{
			{ ShaderDataType::Float3, "aPos" },
			{ ShaderDataType::Float3, "aColor" },
			{ ShaderDataType::Float2, "aTexCoord" },
		};
		m_VBO->SetLayout(layout);


		s_Data->SquareVertexArray->AddVertexBuffers(m_VBO);
		s_Data->SquareVertexArray->SetIndexBuffer(m_EBO);
		
		s_Data->Shader = Shader::Create("E:/Engine_V1/Draxion/Draxion/src/Draxion/Asset/OpenGL/Shaders/Basic.vert"
			, "E:/Engine_V1/Draxion/Draxion/src/Draxion/Asset/OpenGL/Shaders/Basic.frag");

	}
	void Shutdown()
	{
		delete s_Data;
	}
	void Renderer2D::OnWindowResize(unsigned int Width, unsigned int Height)
	{
		RenderCommand::SetViewport(0, 0, Width, Height);
	}
	void Renderer2D::BeginScene(OrthoGraphicCamera& camera)
	{
		s_Data->Shader->Bind();
		s_Data->Shader->SetMat4("u_ViewProjection", camera.GetViewProjectMatrix());
	}
	void Renderer2D::DrawSquare(const glm::vec2& Position, const glm::vec2& Size, const glm::vec4& Color)
	{
		DrawSquare({Position.x,Position.y,0.0f}, Size, Color);
	}
	void Renderer2D::DrawSquare(const glm::vec3& Position, const glm::vec2& Size, const glm::vec4& Color)
	{									
		s_Data->WhiteTexture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), Position) * glm::scale(glm::mat4(1.0f), { Size.x,Size.y,1.0f });

		s_Data->Shader->SetMat4("u_Transform", transform);
		s_Data->Shader->SetInt("u_Texture",0);
		s_Data->Shader->SetFloat4("u_Color", Color);

		s_Data->SquareVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->SquareVertexArray);
	}
	void Renderer2D::DrawSquare(Ref<Texture2D>& texture, const glm::vec2& Position, const glm::vec2& Size, const glm::vec4& Color)
	{
		DrawSquare(texture, {Position.x, Position.y, 0.0f}, Size,Color);
	}
	void Renderer2D::DrawSquare(Ref<Texture2D>& texture, const glm::vec3& Position, const glm::vec2& Size, const glm::vec4& Color)
	{
		texture->Bind();
		
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), Position) * glm::scale(glm::mat4(1.0f), { Size.x,Size.y,1.0f });

		s_Data->Shader->SetMat4("u_Transform", transform);
		s_Data->Shader->SetInt("u_Texture", 0);
		s_Data->Shader->SetFloat4("u_Color", Color);

		s_Data->SquareVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->SquareVertexArray);
	}
	void Renderer2D::EndScene()
	{

	}
}