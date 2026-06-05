#include "OpenGLRenderAPI.h"
#include <glad/glad.h>

namespace Draxion
{
	void OpenGLRenderAPI::Init()
	{ 
		glEnable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	} 

	void OpenGLRenderAPI::SetViewport(unsigned int x, unsigned int y, unsigned int Width, unsigned int Height)
	{
		glViewport(x, y, Width, Height );
	}

	void OpenGLRenderAPI::SetClearColor(const glm::vec4& color)
	{
		glClearColor( color.r, color.g, color.b, color.a );
	}

	void OpenGLRenderAPI::Clear()
	{
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	}

	void OpenGLRenderAPI::DrawIndexed(const Ref<VertexArray>& vertexarray, unsigned int indexcount)
	{
		// Why idxCount is 60,000
		unsigned int idxCount = indexcount ? vertexarray->GetIndexBuffer()->GetCount() : indexcount;
		glDrawElements(GL_TRIANGLES, idxCount, GL_UNSIGNED_INT, nullptr );
	}

}
