#pragma once
#include "Buffer.h"
#include "../../Core/Core.h"

namespace Draxion
{
	class DRX_API VertexArray
	{
	public:
		virtual ~VertexArray() {};

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		 
		virtual void AddVertexBuffers(const std::shared_ptr<VertexBuffer>& vertexBuffer )  = 0;
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer )  = 0;


		virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() = 0;
		virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() = 0;
	public:
		static VertexArray* Create();
	};
}