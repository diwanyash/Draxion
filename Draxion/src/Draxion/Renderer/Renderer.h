#pragma once
#include "Draxion/Renderer/RendererCommand.h"

namespace Draxion
{
	class Renderer
	{
	public:
		static void BeginScene();
		static void Submit( const std::shared_ptr<VertexArray>& vertexarray );
		static void EndScene();

		inline static RenderAPI::API GetAPI() { return RenderAPI::GetAPI(); }
	};
}