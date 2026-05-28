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
		 
		virtual void AddVertexBuffers(const Ref<VertexBuffer>& vertexBuffer )  = 0;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer )  = 0;


		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() = 0;
		virtual const Ref<IndexBuffer>& GetIndexBuffer() = 0;
	public:
		static Ref<VertexArray> Create();
	};
}