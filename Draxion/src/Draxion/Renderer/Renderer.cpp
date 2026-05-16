#include "Renderer.h"
#include "RendererCommand.h"
#include "OrthoGraphicCamera.h"

///////////////////////////
#include "Draxion/Platform/Windows/OpenGL/OpenGLShader.h"

namespace Draxion
{
	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

	void Renderer::Init()
	{
		RenderCommand::Init();
	}
	void Renderer::BeginScene( OrthoGraphicCamera& camera )
	{
		m_SceneData->ViewProjectMatrix = camera.GetViewProjectMatrix();
	}
	void Renderer::Submit(const Ref<Shader>& pShader, const Ref<VertexArray>& vertexarray, const glm::mat4& transform)
	{
		vertexarray->Bind();
		pShader->Bind();

		std::dynamic_pointer_cast<OpenGLShader>(pShader)->UploadUniformMat4( "u_ViewProjection", m_SceneData->ViewProjectMatrix );
		std::dynamic_pointer_cast<OpenGLShader>(pShader)->UploadUniformMat4( "u_Transform", transform );
		RenderCommand::DrawIndexed(vertexarray);
	}
	void Renderer::EndScene()
	{
	}
}
