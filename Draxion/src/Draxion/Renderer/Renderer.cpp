#include "Renderer.h"
#include "RendererCommand.h"

namespace Draxion
{
	void Renderer::BeginScene()
	{
	}
	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexarray)
	{
		vertexarray->Bind();
		RenderCommand::DrawIndexed(vertexarray);
	}
	void Renderer::EndScene()
	{
	}
}
