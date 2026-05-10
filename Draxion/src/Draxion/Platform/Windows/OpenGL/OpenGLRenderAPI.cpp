#include "OpenGLRenderAPI.h"
#include <glad/glad.h>

namespace Draxion
{

	void OpenGLRenderAPI::SetClearColor(const glm::vec4& color)
	{
		glClearColor( color.r, color.g, color.b, color.a );
	}

	void OpenGLRenderAPI::Clear()
	{
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	}

	void OpenGLRenderAPI::DrawIndexed(const std::shared_ptr<VertexArray>& vertexarray)
	{
		glDrawElements( GL_TRIANGLES, vertexarray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr );
	}

}
