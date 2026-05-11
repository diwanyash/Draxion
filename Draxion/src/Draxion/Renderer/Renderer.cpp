#include "Renderer.h"
#include "RendererCommand.h"
#include "OrthoGraphicCamera.h"

namespace Draxion
{
	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

	void Renderer::BeginScene( OrthoGraphicCamera& camera )
	{
		m_SceneData->ViewProjectMatrix = camera.GetViewProjectMatrix();
	}
	void Renderer::Submit(const std::shared_ptr<Shader>& pShader, const std::shared_ptr<VertexArray>& vertexarray)
	{
		vertexarray->Bind();
		pShader->Bind();

		pShader->UploadUniformMat4( "u_ViewProjection", m_SceneData->ViewProjectMatrix );
		RenderCommand::DrawIndexed(vertexarray);
	}
	void Renderer::EndScene()
	{
	}
}
