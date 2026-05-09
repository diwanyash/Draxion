#pragma once
#include "Draxion/Renderer/Buffer/Buffer.h"

namespace Draxion
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer( float* vertices, unsigned int size_B);

		~OpenGLVertexBuffer();

		void Bind() const override;
		void Unbind() const override;

		inline const BufferLayout& const GetLayout() const override { return m_Layout; }
		inline void SetLayout(const BufferLayout& layout) override
		{ 
			m_Layout = layout; 
		}
	private:
		unsigned int m_RendererID;
		BufferLayout m_Layout;
	};


	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer( unsigned int* indices, unsigned int count);

		~OpenGLIndexBuffer();

		unsigned int GetCount() const { return m_Count; }

		void Bind() const override;
		void Unbind() const override;
	private:
		unsigned int m_RendererID;
		unsigned int m_Count;
	};
}