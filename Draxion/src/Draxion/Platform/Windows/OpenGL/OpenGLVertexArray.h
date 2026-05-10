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

		void AddVertexBuffers(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
		void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;

		inline const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() override { return m_VertexBuffers; }
		inline const std::shared_ptr<IndexBuffer>& GetIndexBuffer() override { return m_IndexBuffer; }
	private:
		unsigned int m_RendererID;
		std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
	};
}