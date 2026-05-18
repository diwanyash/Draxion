#pragma once
#include <glm/glm.hpp>
#include "Draxion/Renderer/Buffer/VertexArray.h"

namespace Draxion
{
	class RenderAPI
	{
	public:
		enum class API
		{
			None   = 0,
			OpenGL = 1
		};
	public:
		virtual void Init() = 0;
		virtual void SetViewport( unsigned int x,unsigned int y,unsigned int Width,unsigned int Height ) = 0;

		virtual void SetClearColor( const glm::vec4& color ) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed( const Ref<VertexArray>& vertexarray ) = 0;
	
		inline static API GetAPI() { return s_API; }
	private:
		static API s_API;
	};

}