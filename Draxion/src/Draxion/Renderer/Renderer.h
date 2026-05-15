#pragma once
#include "Draxion/Renderer/RendererCommand.h"
#include "Draxion/Renderer/OrthoGraphicCamera.h"
#include "Shader/Shader.h"

namespace Draxion
{
	class Renderer
	{
	public:
		static void BeginScene( OrthoGraphicCamera& camera );
		static void Submit(const Ref<Shader>& pShader, const Ref<VertexArray>& vertexarray, const glm::mat4& transform = glm::mat4(1.0f));
		static void EndScene();

		inline static RenderAPI::API GetAPI() { return RenderAPI::GetAPI(); }
	private:
		struct SceneData
		{
			glm::mat4 ViewProjectMatrix;
		};
		static SceneData* m_SceneData;
	};
}