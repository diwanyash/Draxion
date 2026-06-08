#include "Core.h"
#include "Renderer2D.h"
#include <array>
#include <glm/ext/matrix_transform.hpp>
#include "Draxion/Renderer/Buffer/VertexArray.h"
#include "Draxion/Renderer/Shader/Shader.h"
#include "Draxion/Renderer/RendererCommand.h"


#include "Draxion/Core/Util/RandomGen.h"
#include "Draxion/Platform/Windows/OpenGL/OpenGLShader.h"

namespace Draxion
{

	struct SquareVertex
	{
		glm::vec3 Position;
		glm::vec4 Color;
		glm::vec2 TexCoord;
		float TextureIndex;
	};
	struct Renderer2DStorage
	{
		const unsigned int MaxSquares = 10000;
		const unsigned int MaxVertices = MaxSquares * 4;
		const unsigned int MaxIndices = MaxSquares * 6;\
		static const unsigned int MaxTextureSlots = 32;

		Ref<VertexArray> SquareVertexArray;
		Ref<VertexBuffer> SquareVertexBuffer;
		Ref<Shader> Shader;

		SquareVertex* SquareVertexBase = nullptr;
		SquareVertex* SquareVertexptr = nullptr;

		unsigned int IndexCount = 0;
		unsigned int TextureSlotIndex = 1;
		std::array<Ref<Texture2D>, MaxTextureSlots> TextureSlots;
	};


	static Renderer2DStorage s_Data;
	
	void Renderer2D::Init()
	{		

		// float vertices[]
		// {
		// 	// POS					// Color			  Tex-Coord
		//  0.0f, 0.0f, 0.0f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f, // Bottom-Left  0
		//  0.0f, 1.0f, 0.0f,		0.0f, 1.0f, 0.0f,		0.0f, 1.0f, // Bottom-Right 1
		//  1.0f, 1.0f, 0.0f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f, // Top-Right    2
		//  1.0f, 0.0f, 0.0f,		0.0f, 0.0f, 1.0f,		1.0f, 0.0f, // Top-Left     3
		// };

		// unsigned int indices[]
		// {
		// 	0,3,1,
		// 	1,3,2,
		// };

		//glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

		s_Data.SquareVertexArray = VertexArray::Create();
		s_Data.SquareVertexBuffer = VertexBuffer::Create( s_Data.MaxVertices * sizeof(SquareVertex));
		s_Data.SquareVertexBuffer->SetLayout
		(
			{
				{ ShaderDataType::Float3, "aPos" },
				{ ShaderDataType::Float4, "aColor" },
				{ ShaderDataType::Float2, "aTexCoord" },
				{ ShaderDataType::Float, "aTextureIndex" }
			}
		);
		s_Data.SquareVertexArray->AddVertexBuffers(s_Data.SquareVertexBuffer);

		s_Data.SquareVertexBase = new SquareVertex[s_Data.MaxVertices];


		unsigned int* SquareIndexBuffer = new unsigned int[s_Data.MaxIndices];
		unsigned int offset = 0;
		for (unsigned int i = 0; i < s_Data.MaxIndices; i += 6)
		{
			SquareIndexBuffer[i + 0] = offset + 0;
			SquareIndexBuffer[i + 1] = offset + 3;
			SquareIndexBuffer[i + 2] = offset + 1;
			
			SquareIndexBuffer[i + 3] = offset + 1;
			SquareIndexBuffer[i + 4] = offset + 3;
			SquareIndexBuffer[i + 5] = offset + 2;

			offset += 4;
		}

		Ref<IndexBuffer> m_EBO = IndexBuffer::Create(SquareIndexBuffer, s_Data.MaxIndices);

		s_Data.SquareVertexArray->Bind();
		s_Data.SquareVertexArray->SetIndexBuffer(m_EBO);
		delete[] SquareIndexBuffer;
		//m_EBO->Bind();

		s_Data.Shader = Shader::Create("E:/Engine_V1/Draxion/Draxion/src/Draxion/Asset/OpenGL/Shaders/Tiled.vert"
			, "E:/Engine_V1/Draxion/Draxion/src/Draxion/Asset/OpenGL/Shaders/Basic.frag"); 

		int sampler[s_Data.MaxTextureSlots];
		for (int i = 0; i < s_Data.MaxTextureSlots; i++)
			sampler[i] = i;

		s_Data.Shader->Bind();
		s_Data.Shader->SetIntArray("u_Texture", sampler, s_Data.MaxTextureSlots );
		
		// Reserved Slot for White Texture
		
		s_Data.TextureSlots[0] = Texture2D::Create("E:/Engine_V1/Draxion/Draxion/src/Draxion/Asset/Images/WhitePixel.png");

	}
	void Shutdown()
	{
	}
	void Renderer2D::OnWindowResize(unsigned int Width, unsigned int Height)
	{
		RenderCommand::SetViewport(0, 0, Width, Height);
	}
	void Renderer2D::BeginScene(OrthoGraphicCamera& camera)
	{
		s_Data.Shader->Bind();
		s_Data.Shader->SetMat4("u_ViewProjection", camera.GetViewProjectMatrix());

		s_Data.IndexCount = 0;
		s_Data.SquareVertexptr = s_Data.SquareVertexBase;

		s_Data.TextureSlotIndex = 1;
	}
	void Renderer2D::DrawSquare(const glm::vec2& Position, const glm::vec2& Size, const glm::vec4& Color)
	{
		DrawSquare({Position.x,Position.y,0.0f}, Size, Color);
	}
	void Renderer2D::DrawSquare(const glm::vec3& Position, const glm::vec2& Size, const glm::vec4& Color)
	{	

		float textureIndex = 0.0f;

		s_Data.SquareVertexptr->Position = Position;
		s_Data.SquareVertexptr->Color = Color;
		s_Data.SquareVertexptr->TexCoord = {0.0f,0.0f};
		s_Data.SquareVertexptr->TextureIndex = textureIndex;
		s_Data.SquareVertexptr++;

		s_Data.SquareVertexptr->Position = { Position.x, Position.y + Size.y, Position.z };
		s_Data.SquareVertexptr->Color = Color;
		s_Data.SquareVertexptr->TexCoord = {0.0f,1.0f};
		s_Data.SquareVertexptr->TextureIndex = textureIndex;
		s_Data.SquareVertexptr++;

		s_Data.SquareVertexptr->Position = { Position.x + Size.x, Position.y + Size.y, Position.z };
		s_Data.SquareVertexptr->Color = Color;
		s_Data.SquareVertexptr->TexCoord = {1.0f,1.0f};
		s_Data.SquareVertexptr->TextureIndex = textureIndex;
		s_Data.SquareVertexptr++;

		s_Data.SquareVertexptr->Position = { Position.x + Size.x, Position.y, Position.z };
		s_Data.SquareVertexptr->Color = Color;
		s_Data.SquareVertexptr->TexCoord = {1.0f,0.0f};
		s_Data.SquareVertexptr->TextureIndex = textureIndex;
		s_Data.SquareVertexptr++;

		s_Data.IndexCount += 6;

		//	glm::mat4 transform = glm::translate(glm::mat4(1.0f), Position) * glm::scale(glm::mat4(1.0f), { Size.x,Size.y,1.0f });
		//	
		//	s_Data.Shader->SetMat4("u_Transform", transform);
		//	s_Data.Shader->SetInt("u_Texture",0);
		//	s_Data.Shader->SetFloat4("u_Color", Color);
		//	
		//	s_Data.SquareVertexArray->Bind();
		//	RenderCommand::DrawIndexed(s_Data.SquareVertexArray);
	}
	void Renderer2D::DrawSquare(const Ref<Texture2D>& texture, const glm::vec3& Position, const glm::vec2& Size, const glm::vec4& Color)
	{
		// Test Only!!!!!!!
		// s_Data.Shader->Bind();
		// s_Data.Shader->SetInt2("u_Grid", glm::ivec2(RandomGen::Get<int>(0,3), RandomGen::Get<int>(0, 3)));
		//s_Data.Shader->SetFloat2("Grid", {1.0f,2.0f});

		float textureIndex = 0.0f;

		for (unsigned int i = 1;i < s_Data.TextureSlotIndex; i++)
		{
			if ( s_Data.TextureSlots[i]->GetRendererID() == texture->GetRendererID() )
			{
				textureIndex = (float)i;
				break;
			}
		}

		if ( textureIndex == 0.0f )
		{
			textureIndex = (float)s_Data.TextureSlotIndex;
			s_Data.TextureSlots[s_Data.TextureSlotIndex] = texture;
			s_Data.TextureSlotIndex++;
		}

		s_Data.SquareVertexptr->Position = Position;
		s_Data.SquareVertexptr->Color = Color;
		s_Data.SquareVertexptr->TexCoord = { 0.0f,0.0f };
		s_Data.SquareVertexptr->TextureIndex = textureIndex;
		s_Data.SquareVertexptr++;

		s_Data.SquareVertexptr->Position = { Position.x, Position.y + Size.y, Position.z };
		s_Data.SquareVertexptr->Color = Color;
		s_Data.SquareVertexptr->TexCoord = { 0.0f,1.0f };
		s_Data.SquareVertexptr->TextureIndex = textureIndex;
		s_Data.SquareVertexptr++;

		s_Data.SquareVertexptr->Position = { Position.x + Size.x, Position.y + Size.y, Position.z };
		s_Data.SquareVertexptr->Color = Color;
		s_Data.SquareVertexptr->TexCoord = { 1.0f,1.0f };
		s_Data.SquareVertexptr->TextureIndex = textureIndex;
		s_Data.SquareVertexptr++;

		s_Data.SquareVertexptr->Position = { Position.x + Size.x, Position.y, Position.z };
		s_Data.SquareVertexptr->Color = Color;
		s_Data.SquareVertexptr->TexCoord = { 1.0f,0.0f };
		s_Data.SquareVertexptr->TextureIndex = textureIndex;
		s_Data.SquareVertexptr++;

		s_Data.IndexCount += 6;

		//	texture->Bind();
		//	
		//	glm::mat4 transform = glm::translate(glm::mat4(1.0f), Position) * glm::scale(glm::mat4(1.0f), { Size.x,Size.y,1.0f });
		//	
		//	s_Data.Shader->SetMat4("u_Transform", transform);
		//	s_Data.Shader->SetInt("u_Texture", 0);
		//	s_Data.Shader->SetFloat4("u_Color", Color);
		//	
		//	s_Data.SquareVertexArray->Bind();
		//	RenderCommand::DrawIndexed(s_Data.SquareVertexArray);
	}
	void Renderer2D::DrawSquare(const Ref<Texture2D>& texture, const glm::vec2& Position, const glm::vec4& UV, const glm::vec2& Size, const glm::vec4& Color)
	{
		DrawSquare(texture, {Position.x,Position.y,0.0f}, UV, Size, Color);
	}
	void Renderer2D::DrawSquare(const Ref<Texture2D>& texture, const glm::vec3& Position,const glm::vec4& UV, const glm::vec2& Size, const glm::vec4& Color)
	{
		float textureIndex = 0.0f;

		for (unsigned int i = 1; i < s_Data.TextureSlotIndex; i++)
		{
			if ( s_Data.TextureSlots[i]->GetRendererID() == texture->GetRendererID() )
			{
				textureIndex = (float)i;
				break;
			}
		}

		if (textureIndex == 0.0f)
		{
			textureIndex = (float)s_Data.TextureSlotIndex;
			s_Data.TextureSlots[s_Data.TextureSlotIndex] = texture;
			s_Data.TextureSlotIndex++;
		}

		s_Data.SquareVertexptr->Position = Position;
		s_Data.SquareVertexptr->Color = Color;
		s_Data.SquareVertexptr->TexCoord = { UV.x,UV.y};
		s_Data.SquareVertexptr->TextureIndex = textureIndex;
		s_Data.SquareVertexptr++;

		s_Data.SquareVertexptr->Position = { Position.x, Position.y + Size.y, Position.z };
		s_Data.SquareVertexptr->Color = Color;
		s_Data.SquareVertexptr->TexCoord = { UV.x,UV.w };
		s_Data.SquareVertexptr->TextureIndex = textureIndex;
		s_Data.SquareVertexptr++;

		s_Data.SquareVertexptr->Position = { Position.x + Size.x, Position.y + Size.y, Position.z };
		s_Data.SquareVertexptr->Color = Color;
		s_Data.SquareVertexptr->TexCoord = { UV.z,UV.w };
		s_Data.SquareVertexptr->TextureIndex = textureIndex;
		s_Data.SquareVertexptr++;

		s_Data.SquareVertexptr->Position = { Position.x + Size.x, Position.y, Position.z };
		s_Data.SquareVertexptr->Color = Color;
		s_Data.SquareVertexptr->TexCoord = { UV.z,UV.y };
		s_Data.SquareVertexptr->TextureIndex = textureIndex;
		s_Data.SquareVertexptr++;

		s_Data.IndexCount += 6;
	}
	void Renderer2D::SetGrid(const glm::ivec2& value)
	{
		s_Data.Shader->Bind();
		s_Data.Shader->SetInt2("u_Grid", glm::ivec2(value.x, value.y));
	}
	void Renderer2D::EndScene()
	{
		__int64 datasize = (uint8_t*)s_Data.SquareVertexptr - (uint8_t*)s_Data.SquareVertexBase;
		s_Data.SquareVertexBuffer->SetData( s_Data.SquareVertexBase, datasize );

		Flush(); 
	}
	void Renderer2D::Flush()
	{
		for (unsigned int i = 0; i < s_Data.TextureSlotIndex; i++)
		{
			s_Data.TextureSlots[i]->Bind(i);
		}

		RenderCommand::DrawIndexed(s_Data.SquareVertexArray, s_Data.IndexCount );
	}
}