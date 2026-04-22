#include "Application.h"
#include "../Platform/Windows/Window.h"
#include "Logger.h"
#include <Events/EventDispatcher.h>
#include <Events/KeyEvent.h>
#include <Events/MouseEvent.h>
#include <Input/KeyCodes.h>

namespace Draxion
{
	// CTOR
	Application::Application()
	{
		m_Window.reset(Window::CreateWindow( 800, 600, "Lucky" ));
		s_Instance = this;
	}
	// DTOR
	Application::~Application() = default;

	void Application::Run()
	{
		while (!m_Window->ShouldClose())
		{
			m_Window->OnUpdate();
			OnUpdate();
		}
	}
	Application& Application::Get()
	{
		return *s_Instance;
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher d(e);
		d.Dispatch<KeyPressedEvent>([&](KeyPressedEvent& e)
		{
			if ((e.GetKeyCode()) == Draxion::Key::VK_ESCAPE)
			{
				GetWindow().SetShouldClose(true);
			}
			return true;
		});
		d.Dispatch<MouseEvent>([&](MouseEvent& e)
		{
			if ((e.GetKeyCode()) == Draxion::Key::MOUSE_BUTTON_LEFT)
			{
				//LOG_ENGINE_TRACE( "MousePos{" << e.GetXpos() << "," << e.GetYpos() << "}");
			}
			return true;
		});
	}

	Window& Application::GetWindow()
	{
		return *m_Window;
	}

	Application* Application::s_Instance = nullptr;
}

