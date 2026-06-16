#include "Renderer.h"
#include "Renderer2D.h"
#include "RendererCommand.h"
#include "OrthoGraphicCamera.h"

///////////////////////////
#include "Draxion/Platform/Windows/OpenGL/OpenGLShader.h"
#include <Draxion/Debug/Profiler/ProfileTimer.h>

namespace Draxion
{
	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

	void Renderer::Init()
	{
		RenderCommand::Init();
		Renderer2D::Init();
	}
	void Renderer::OnWindowResize(unsigned int Width, unsigned int Height)
	{
		RenderCommand::SetViewport(0, 0, Width, Height);
	}
	void Renderer::BeginScene( OrthoGraphicCamera& camera )
	{
		m_SceneData->ViewProjectMatrix = camera.GetViewProjectMatrix();
	}
	void Renderer::Submit(const Ref<Shader>& pShader, const Ref<VertexArray>& vertexarray, const glm::mat4& transform)
	{
		DX_PROFILE_FUNCTION();

		vertexarray->Bind();
		pShader->Bind();

		pShader->SetMat4( "u_ViewProjection", m_SceneData->ViewProjectMatrix );
		pShader->SetMat4( "u_Transform", transform );
		RenderCommand::DrawIndexed(vertexarray);
	}
	void Renderer::EndScene()
	{
		DX_PROFILE_FUNCTION();


	}
}
