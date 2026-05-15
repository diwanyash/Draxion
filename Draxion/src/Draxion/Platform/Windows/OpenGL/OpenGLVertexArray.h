#pragma once
#include "Draxion/Renderer/Buffer/VertexArray.h"

namespace Draxion
{
	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		~OpenGLVertexArray() override;


		void Bind() const override;
		void Unbind() const override;

		void AddVertexBuffers(const Ref<VertexBuffer>& vertexBuffer) override;
		void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;

		inline const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() override { return m_VertexBuffers; }
		inline const Ref<IndexBuffer>& GetIndexBuffer() override { return m_IndexBuffer; }
	private:
		unsigned int m_RendererID;
		std::vector<Ref<VertexBuffer>> m_VertexBuffers;
		Ref<IndexBuffer> m_IndexBuffer;
	};
}