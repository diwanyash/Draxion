#pragma once
/// <summary>
#ifdef DRX_ENGINE
#include "glad/glad.h"
#include "Draxion/Core/Logger.h"
#endif
/// </summary>


#include "../../Core/Core.h"
#include <memory>
#include <vector>
#include <String>



namespace Draxion
{
	enum DRX_API ShaderDataType
	{
		None = 0,
		Float,
		Float2,
		Float3,
		Float4,
		Int,
		Int2,
		Int3,
		Int4,
		Mat2,
		Mat3,
		Mat4,
		Bool
	};

	static unsigned int ShaderDataTypeSize( ShaderDataType type )
	{
		switch (type)
		{
		case ShaderDataType::Float:		return 4;
		case ShaderDataType::Float2:	return 4 * 2;
		case ShaderDataType::Float3:	return 4 * 3;
		case ShaderDataType::Float4:	return 4 * 4;
		case ShaderDataType::Int:		return 4;
		case ShaderDataType::Int2:		return 4 * 2;
		case ShaderDataType::Int3:		return 4 * 3;
		case ShaderDataType::Int4:		return 4 * 4;
		case ShaderDataType::Mat2:		return 4 * 2 * 2;
		case ShaderDataType::Mat3:		return 4 * 3 * 3;
		case ShaderDataType::Mat4:		return 4 * 4 * 4;
		case ShaderDataType::Bool:		return 1;
		}

		LOG_CLIENT_ERROR("Unknown ShaderDataType");
		return 0;
	}

	class DRX_API BufferElement
	{
	public:
		BufferElement( ShaderDataType type,const std::string& name, bool normalized = false )
			:
			m_type(type),
			m_name(name),
			size( ShaderDataTypeSize(type) ),
			offset(0),
			normalize(normalized)
		{}

		inline unsigned int GetComponentCount() const
		{
			switch (m_type)
			{
				case ShaderDataType::Float:		return 1;
				case ShaderDataType::Float2:	return 2;
				case ShaderDataType::Float3:	return 3;
				case ShaderDataType::Float4:	return 4;
				case ShaderDataType::Int:		return 1;
				case ShaderDataType::Int2:		return 2;
				case ShaderDataType::Int3:		return 3;
				case ShaderDataType::Int4:		return 4;
				case ShaderDataType::Mat2:		return 2 * 2;
				case ShaderDataType::Mat3:		return 3 * 3;
				case ShaderDataType::Mat4:		return 4 * 4;
				case ShaderDataType::Bool:		return 1;
			}


			LOG_CLIENT_ERROR("Unknown ShaderDataType");
			return 0;
		}
	public:
		std::string m_name;
		ShaderDataType m_type;
		unsigned int offset;
		unsigned int size;
		bool normalize;
	};

	class DRX_API BufferLayout
	{
	public:
		BufferLayout() {}
		BufferLayout(const std::initializer_list<BufferElement>& elements)
			:
			m_Elements(elements)
		{
			CalculateStrideAndOffset();
		}
		inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }
		inline const unsigned int GetStride() const { return m_Stride; }

		std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); };
		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); };
	private:
 		inline void CalculateStrideAndOffset()
		{
			unsigned int Offset = 0;
			m_Stride = 0;
			for (auto& element : m_Elements )
			{
				element.offset = Offset;
				Offset += element.size;
				m_Stride += element.size;
			}
		}
	private:
		std::vector<BufferElement> m_Elements;
		unsigned int m_Stride = 0;
	};

	class DRX_API VertexBuffer
	{
	public:
		virtual ~VertexBuffer() {};

		static Ref<VertexBuffer> Create( unsigned int size_B );
		static Ref<VertexBuffer> Create( float* vertices, unsigned int size_B );
	
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual const BufferLayout& GetLayout() const = 0;
		virtual void SetLayout(const BufferLayout& layout ) = 0;
		virtual void SetData(const void* data, long long int size ) = 0;
	};

	class DRX_API IndexBuffer
	{
	public:
		virtual ~IndexBuffer() {};

		static Ref<IndexBuffer> Create(unsigned int* indices, unsigned int count );
		
		virtual unsigned int GetCount() const = 0;
	
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
	};
}