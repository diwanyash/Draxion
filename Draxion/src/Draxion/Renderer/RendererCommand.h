#pragma once
#include "Buffer/VertexArray.h"
#include "../Core/Core.h"

namespace Draxion
{
	class DRX_API RendererCommand
	{
	public:
		static void Init();

		static void SetClearColor( float r, float g, float b, float a );
		static void Clear();
		static void DrawIndexed(const VertexArray& vao, unsigned int count);
	private:
	};
}