#pragma once
#include "Draxion/Renderer/RenderAPI.h"

namespace Draxion
{

	class OpenGLRenderAPI : public RenderAPI
	{
	public:
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexarray) override;
	};

}