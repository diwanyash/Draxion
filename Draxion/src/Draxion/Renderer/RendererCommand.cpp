#include "RendererCommand.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../Core/Logger.h"

////// LATER TO_BE REMOVED/////////
#include <string>
///////////////////////////////////

namespace Draxion
{
	void RendererCommand::Init()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_DEPTH_TEST);
	}

	void RendererCommand::SetClearColor( float r, float g, float b, float a )
	{
		glClearColor(r, g, b, a);
	}
	void RendererCommand::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	void RendererCommand::DrawIndexed( const VertexArray& vao, unsigned int count )
	{
		vao.Bind();
		glDrawElements(GL_TRIANGLES,count, GL_UNSIGNED_INT, nullptr );
	}
}