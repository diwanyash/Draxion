#pragma once
#include "Draxion/Renderer/RenderAPI.h"

namespace Draxion
{

	class OpenGLRenderAPI : public RenderAPI
	{
	public:
		void Init() override;
		void SetViewport( unsigned int x, unsigned int y, unsigned int Width, unsigned int Height );
		void SetClearColor(const glm::vec4& color) override;
		void Clear() override;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexarray, unsigned int indexcount) override;
	};

}