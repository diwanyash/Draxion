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
		static void Submit(const std::shared_ptr<Shader>& pShader, const std::shared_ptr<VertexArray>& vertexarray );
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