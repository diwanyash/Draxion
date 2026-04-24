#pragma once
#include "../../Core/Core.h"

namespace Draxion
{
	class DRX_API VertexBuffer
	{
	public:
		VertexBuffer( float* vertices, unsigned int size_B );
		~VertexBuffer();
	
		void Bind() const;
		void Unbind() const;
	private:
		unsigned int m_RendererID;
	};
}