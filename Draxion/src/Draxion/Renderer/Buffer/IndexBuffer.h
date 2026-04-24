#pragma once
#include "../../Core/Core.h"

namespace Draxion
{
	class DRX_API IndexBuffer
	{
	public:
		IndexBuffer(unsigned int* indices, unsigned int icount);
		~IndexBuffer();

		unsigned int GetCount() const { return m_Count; }

		void Bind() const;
		void Unbind() const;
	private:
		unsigned int m_RendererID;
		unsigned int m_Count;
	};
}