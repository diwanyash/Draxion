#pragma once
#include "Draxion/Renderer/RenderAPI.h"
#include "Buffer/VertexArray.h"
#include "../Core/Core.h"


/*///////////////////////////
glEnable(GL_BLEND);
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
glEnable(GL_DEPTH_TEST);
////////////////////////////*/


namespace Draxion
{
	class DRX_API RenderCommand
	{
	public:
		inline static void SetClearColor(const glm::vec4& color)
		{
			s_RenderAPI->SetClearColor(color);
		}
		inline static void Clear()
		{
			s_RenderAPI->Clear();
		}
		inline static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexarray)
		{
			s_RenderAPI->DrawIndexed( vertexarray );
		}
	private:
		static RenderAPI* s_RenderAPI;
		static bool isWireframe;
	};
}