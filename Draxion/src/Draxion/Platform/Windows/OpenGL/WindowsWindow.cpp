#include "WindowsWindow.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <cassert>


#include "Draxion/Events/ApplicationEvent.h"
#include "Draxion/Events/KeyEvent.h"
#include "Draxion/Events/MouseEvents.h"
#include "Draxion/Renderer/Renderer.h"
#include "Draxion/Core/Logger.h"
////////////////IMGUI//////////
#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_opengl3.h>
#include <ImGui/imgui_impl_glfw.h>
//////////////////////////////////


namespace Draxion
{
	WindowsWindow::WindowsWindow( int width, int height, const std::string& title )
	{
		m_Data.m_Width = width;
		m_Data.m_Height = height;
		m_Data.m_Title = title;

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
		//auto ver = glGetString(GL_VERSION);
		//LOG_ENGINE_TRACE(ver);
		glViewport(0, 0, width, height);


		glfwSetWindowUserPointer(m_Window,&m_Data);

		//glfwSetFramebufferSizeCallback(m_Window, []( GLFWwindow* window, int width, int height) 
		//{
		//});

		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) 
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.m_Width = width;
			data.m_Height = height;

			Draxion::WindowsResizeEvent event(width, height);
			data.EventFn(event);

			glViewport(0, 0, width, height);
			LOG_ENGINE_TRACE( "W = " << data.m_Width << " H = " << data.m_Height);
		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			WindowData& Data = *(WindowData*)glfwGetWindowUserPointer(window);
     		switch (action)
			{
			case GLFW_PRESS:
			{
				//Draxion::Application::Get().OnEvent(event);
				Draxion::KeyPressedEvent event(key);
				Data.EventFn(event);
				break;
			}
			case GLFW_RELEASE:
			{
				Draxion::KeyReleasedEvent event(key);
				Data.EventFn(event);
				break;
			}
			case GLFW_REPEAT:
			{
				Draxion::KeyRepeatEvent event(key,1);
				Data.EventFn(event);
				break;
			}
			default:
				break;
			}
		});

		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			Draxion::KeyTypedEvent event(keycode);
			data.EventFn(event);
		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
		{
			WindowData& Data = *(WindowData*)glfwGetWindowUserPointer(window);

			//glfwGetCursorPos(window, &posx, &posy);
			switch(action)
			{
				case GLFW_PRESS:
				{
					Draxion::MouseButtonPressed event(button);
					Data.EventFn(event);
					break;
				}
				case GLFW_RELEASE:
				{
					Draxion::MouseButtonReleased event(button);
					Data.EventFn(event);
					break;
				}
			}
		});
		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			WindowData& Data = *(WindowData*)glfwGetWindowUserPointer(window);
			Draxion::MouseScrolledEvent event((int)xOffset, (int)yOffset);
			Data.EventFn(event);
		});
		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
		{
			WindowData& Data = *(WindowData*)glfwGetWindowUserPointer(window);
			Draxion::MouseMovedEvent event((int)xPos, (int)yPos);
			Data.EventFn(event);
		});
		glfwSetErrorCallback([](int error, const char* desc)
		{
			LOG_ENGINE_ERROR(error << "::" << desc);
		});
		LOG_ENGINE_TRACE("WindowsWindow Constructed");
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

	inline void WindowsWindow::SetEventCallback(const std::function<void(Event&)>& callback)
	{
		m_Data.EventFn = callback;
	}

}