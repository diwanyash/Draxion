#include "OpenGLContext.h"
#include "Draxion/Core/Logger.h"

#include "glad/glad.h"
#include "glfw/glfw3.h"

namespace Draxion
{
	OpenGLContext::OpenGLContext(GLFWwindow* Windowhandle)
		:
		m_Windowhandle(Windowhandle)
	{
		if(Windowhandle == nullptr)
		LOG_ENGINE_FATAL("Window-Handle is NULL");
	}
	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_Windowhandle);
		// IF V-SYNC IS DISABLED
		glfwSwapInterval(1);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			LOG_ENGINE_FATAL("OPENGL failed At GLADLoadGLLoader");
		}

		LOG_ENGINE_INFO( "Graphics Card Vendor :- " << glGetString( GL_VENDOR ));
		LOG_ENGINE_INFO( "Graphics Card Info :- " << glGetString( GL_RENDERER ));
		LOG_ENGINE_INFO( "Shading Lnaguage Support :- " << glGetString( GL_SHADING_LANGUAGE_VERSION ));
	}
	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_Windowhandle);
	}
}