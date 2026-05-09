#pragma once
#include "Buffer.h"
#include "../../Core/Core.h"

namespace Draxion
{
	class DRX_API VertexArray
	{
	public:
		VertexArray();
		~VertexArray();

		void Bind() const;
		void Unbind() const;

		void AddBuffer(const VertexBuffer& vb ) const ;
	private:
		unsigned int m_RendererID;
	};
}