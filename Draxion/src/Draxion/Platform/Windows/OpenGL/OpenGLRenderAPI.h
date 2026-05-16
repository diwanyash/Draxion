#pragma once
#include "Draxion/Renderer/RenderAPI.h"

namespace Draxion
{

	class OpenGLRenderAPI : public RenderAPI
	{
	public:
		void Init() override;
		void SetClearColor(const glm::vec4& color) override;
		void Clear() override;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexarray) override;
	};

}