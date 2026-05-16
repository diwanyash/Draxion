#include "OpenGLRenderAPI.h"
#include <glad/glad.h>

namespace Draxion
{
	void OpenGLRenderAPI::Init()
	{ 
		glEnable(GL_BLEND);
		glDisable(GL_DEPTH_TEST);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void OpenGLRenderAPI::SetClearColor(const glm::vec4& color)
	{
		glClearColor( color.r, color.g, color.b, color.a );
	}

	void OpenGLRenderAPI::Clear()
	{
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	}

	void OpenGLRenderAPI::DrawIndexed(const Ref<VertexArray>& vertexarray)
	{
		glDrawElements( GL_TRIANGLES, vertexarray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr );
	}

}
