#include "WindowsWindow.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <cassert>
#include <string>
#include "../../Events/KeyEvent.h"
#include "../../Events/MouseEvent.h"
#include "../../Core/Application.h"
#include <Core/Logger.h>

namespace Draxion
{
	WindowsWindow::WindowsWindow( int width, int height, const std::string& title )
	{
		if (!glfwInit())
		{
			assert(false);
		}

		m_Window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
		assert(m_Window);
		glfwMakeContextCurrent(m_Window);
		glfwSwapInterval(1);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			assert(false && "OPENGL failed At GLADLoadGLLoader");
		}
		glfwSetWindowUserPointer(m_Window, this);

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			if (action == GLFW_PRESS)
			{
				Draxion::KeyPressedEvent event(key);
				Draxion::Application::Get().OnEvent(event);
			}
		});
		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
		{
			if (action == GLFW_PRESS)
			{
				double posx = 0.0, posy = 0.0;
				glfwGetCursorPos(window, &posx, &posy);
				Draxion::MouseEvent event(button, posx, posy);
				Draxion::Application::Get().OnEvent(event);
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
		glViewport(0, 0, 800, 600);
		glClearColor( 0.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
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