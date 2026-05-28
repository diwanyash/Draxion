#include "Application.h"
#include "Logger.h"
#include "Window.h"
////////////////////////////////
#include "Draxion/Input/Input.h"
#include "Draxion/Input/KeyCodes.h"
#include "Draxion/Core/Util/TimeStamp.h"
////////////////////////////////
#include "Draxion/Events/EventDispatcher.h"
#include "Draxion/Events/KeyEvent.h"
#include "Draxion/Events/MouseEvents.h"

////////////////////////////////
#include "Draxion/Renderer/RendererCommand.h"
#include "Draxion/Renderer/Renderer.h"
#include "Draxion/Renderer/Renderer2D.h"
/////////////////////////////
#include <GLFW/glfw3.h>
/////////////////////////////

#include "Util/RandomGen.h"

namespace Draxion
{
	// CTOR
	Application::Application()
	{
		LOG_ENGINE_TRACE("Application Constructing");
		m_Window.reset(Window::CreateWindow( 1280, 720, "Lucky" ));
		m_Window->SetEventCallback([this](Event& e) { this->OnEvent(e); });
		s_Instance = this;

		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverLay(m_ImGuiLayer);

		LOG_ENGINE_TRACE("Application Constructed");
	}
	// DTOR
	Application::~Application() = default;

	void Application::Run()
	{

		while (!m_Window->ShouldClose())
		{
			float time = (float)glfwGetTime();
			TimeStamp dt = time - m_last_time;
			m_last_time = time;

			for (Layer* lay : m_Layer_Stack)
				lay->OnUpdate(dt);

			m_ImGuiLayer->Begin();
			for (Layer* lay : m_Layer_Stack)
				lay->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}
	Application& Application::Get()
	{
		return *s_Instance;
	}
	void Application::OnUpdate()
	{
		//Later // to avoid warnings 
	}
	void Application::PushLayer( Layer* iLayer )
	{
		m_Layer_Stack.PushLayer( iLayer );
	}
	void Application::PushOverLay( Layer* iOverLay )
	{
		m_Layer_Stack.PushOverLay( iOverLay );
	}
	void Application::PopLayer( Layer* iLayer )
	{
		m_Layer_Stack.PopLayer( iLayer );
	}
	void Application::PopOverLay( Layer* iOverLay )
	{
		m_Layer_Stack.PopOverLay( iOverLay );
	}
	void Application::OnEvent(Event& e)
	{
		EventDispatcher d(e);
		d.Dispatch<KeyPressedEvent>([&](KeyPressedEvent& e)
		{
			if ((e.GetKeyCode()) == DRX_KEY_ESCAPE)
			{
				GetWindow().SetShouldClose(true);
			}
			return false;
		});
		
		d.Dispatch<MouseMovedEvent>([](MouseMovedEvent& e)
		{
			e.Handled = false;
			return false;
		});
		
		d.Dispatch<WindowsResizeEvent>([](WindowsResizeEvent& e)
		{
			Renderer::OnWindowResize( e.GetWidth(), e.GetHeight() );
			Renderer2D::OnWindowResize( e.GetWidth(), e.GetHeight() );

			e.Handled = false;
			return false;
		});

		//LOG_ENGINE_TRACE(e.GetName());

		for ( auto it = m_Layer_Stack.end(); it != m_Layer_Stack.begin(); )
		{
			(*--it)->OnEvent(e);

			if ( e.Handled )
				break;
		}
	}

	Window& Application::GetWindow()
	{
		return *m_Window;
	}

	Application* Application::s_Instance = nullptr;
}

