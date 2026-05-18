#define GLFW_INCLUDE_NONE
#include "WindowsWindow.h"
#include "GLFW/glfw3.h"
#include <cassert>


#include "Draxion/Events/ApplicationEvent.h"
#include "Draxion/Events/KeyEvent.h"
#include "Draxion/Events/MouseEvents.h"
#include "Draxion/Renderer/Renderer.h"
#include "Draxion/Core/Logger.h"

#include "Draxion/Platform/Windows/OpenGL/OpenGLContext.h"


namespace Draxion
{
	WindowsWindow::WindowsWindow( int width, int height, const std::string& title )
	{
		WindowsWindow::Init(width, height, title);
	}
	WindowsWindow::~WindowsWindow()
	{
		WindowsWindow::Shutdown();
	}
	void* WindowsWindow::GetNativeWindow() const
	{
		return m_Window;
	}
	void WindowsWindow::Init( int width, int height, const std::string& title )
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
		
		// this OpenGlContext should not be here <Fix>
		m_Context = new OpenGLContext(m_Window);
		m_Context->Init();

		glfwSetWindowUserPointer(m_Window, &m_Data);

		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.m_Width = width;
			data.m_Height = height;

			Draxion::WindowsResizeEvent event(width, height);
			data.EventFn(event);
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
					Draxion::KeyRepeatEvent event(key, 1);
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
			switch (action)
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
	void WindowsWindow::Shutdown()
	{
		delete m_Context;
		m_Context = nullptr;

		glfwDestroyWindow(m_Window);
		glfwTerminate();
	}
	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		m_Context->SwapBuffers();
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