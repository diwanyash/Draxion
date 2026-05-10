#include "OpenGLVertexArray.h"
#include "STB/stb_image.h"

namespace Draxion
{
	static GLenum ShaderDataTypeToGLDataType(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float:		return GL_FLOAT;
		case ShaderDataType::Float2:	return GL_FLOAT;
		case ShaderDataType::Float3:	return GL_FLOAT;
		case ShaderDataType::Float4:	return GL_FLOAT;
		case ShaderDataType::Int:		return GL_INT;
		case ShaderDataType::Int2:		return GL_INT;
		case ShaderDataType::Int3:		return GL_INT;
		case ShaderDataType::Int4:		return GL_INT;
		case ShaderDataType::Mat2:		return GL_FLOAT;
		case ShaderDataType::Mat3:		return GL_FLOAT;
		case ShaderDataType::Mat4:		return GL_FLOAT;
		case ShaderDataType::Bool:		return GL_BOOL;
		}

		LOG_CLIENT_ERROR("Unknown ShaderDataType to GLDataType Conversion");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_RendererID);
	}
	OpenGLVertexArray::~OpenGLVertexArray()
	{ 
		glDeleteVertexArrays(1, &m_RendererID);
	}
	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}
	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}
	void OpenGLVertexArray::AddVertexBuffers(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		if (vertexBuffer->GetLayout().GetElements().size() == 0)
		{
			LOG_ENGINE_ERROR( "No Layout Was Bound Before Calling func AddVertexBuffers()" );
		}

		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();

		auto index = 0;
		for (const auto& element : vertexBuffer->GetLayout())
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, element.GetComponentCount(),
				ShaderDataTypeToGLDataType(element.m_type),
				element.normalize ? GL_TRUE : GL_FALSE, vertexBuffer->GetLayout().GetStride(), (void*)(element.offset));
			index++;
		}

		m_VertexBuffers.push_back(vertexBuffer);


		////////////////TO_BE_DELETED////////////////////////
		unsigned int texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		//glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		int width, height, nrChannels;
		const char* TexPath = "E:/Engine_V1/Draxion/Draxion/src/Draxion/Asset/Images/Neduko.jpg";
		stbi_set_flip_vertically_on_load(true); // Flip on Loading
		unsigned char* TexData = stbi_load(TexPath, &width, &height, &nrChannels, 0);
		if (TexData == NULL)
		{
			LOG_ENGINE_ERROR("Texture Failed to Load::Path:- " << TexPath);
		}


		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, TexData);

		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(TexData);
		/////////////////////////////////////////////////////
	}
	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}
}