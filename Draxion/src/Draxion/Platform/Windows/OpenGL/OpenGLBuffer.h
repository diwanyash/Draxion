#pragma once
#include "Draxion/Renderer/Buffer/Buffer.h"
#include <Draxion/Debug/Profiler/ProfileTimer.h>

namespace Draxion
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer( unsigned int size_B );
		OpenGLVertexBuffer( float* vertices, unsigned int size_B);

		~OpenGLVertexBuffer();

		void Bind() const override;
		void Unbind() const override;
		void SetData(const void* data, long long int size) override;

		inline const BufferLayout& GetLayout() const override { return m_Layout; }
		inline void SetLayout(const BufferLayout& layout) override
		{
			DX_PROFILE_FUNCTION();

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

		unsigned int GetCount() const override { return m_Count; }

		void Bind() const override;
		void Unbind() const override;
	private:
		unsigned int m_RendererID;
		unsigned int m_Count;
	};
}