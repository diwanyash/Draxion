#pragma once
#include "Draxion/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Draxion
{
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext( GLFWwindow* Windowhandle );
		void Init() override;
		void SwapBuffers() override;
	private:
		GLFWwindow* m_Windowhandle;
	};
}