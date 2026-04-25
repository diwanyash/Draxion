#include "WindowsWindow.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Draxion/Events/KeyEvent.h"
#include "Draxion/Events/MouseEvent.h"
#include "Draxion/Core/Application.h"
#include "Draxion/Renderer/Renderer.h"
#include "Draxion/Core/Logger.h"
#include <cassert>

namespace Draxion
{
	WindowsWindow::WindowsWindow( int width, int height, const std::string& title )
	{
		if (!glfwInit())
		{
			LOG_ENGINE_ERROR("GLFW Init Failed");
		}

		m_Window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
		assert(m_Window);
		glfwMakeContextCurrent(m_Window);
		glfwSwapInterval(1);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			LOG_ENGINE_FATAL("OPENGL failed At GLADLoadGLLoader");
		}

		Renderer::Init();
		auto ver = glGetString(GL_VERSION);
		LOG_ENGINE_TRACE(ver);
		glViewport(0, 0, width, height);

		glfwSetFramebufferSizeCallback(m_Window, []( GLFWwindow* window, int width, int height) 
		{
			glViewport(0, 0, width, height);
		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			switch (action)
			{
			case GLFW_PRESS:
			{
				Draxion::KeyPressedEvent event(key);
				Draxion::Application::Get().OnEvent(event);
				break;
			}
			case GLFW_RELEASE:
			{
				Draxion::KeyReleasedEvent event(key);
				Draxion::Application::Get().OnEvent(event);
				break;
			}
			default:
				break;
			}
		});
		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
		{
			double posx = 0.0, posy = 0.0;
			glfwGetCursorPos(window, &posx, &posy);
			Draxion::MouseEvent event(button, (int)posx, (int)posy);

			switch(action)
			{
			case GLFW_PRESS:
				Draxion::Application::Get().OnEvent(event);
				break;
			case GLFW_RELEASE:
				Draxion::Application::Get().OnEvent(event);
				break;
			default:
				break;
			}
		});
	}
	WindowsWindow::~WindowsWindow()
	{
		glfwDestroyWindow(m_Window);
		glfwTerminate();
	}
	void* WindowsWindow::GetNativeWindow() const
	{
		return m_Window;
	}
	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}
	bool WindowsWindow::ShouldClose()
	{
		return glfwWindowShouldClose(m_Window);
	}

	void WindowsWindow::SetShouldClose(bool flag)
	{
		LOG_ENGINE_TRACE("Shutting Down...");
		glfwSetWindowShouldClose(m_Window, flag);
	}

}