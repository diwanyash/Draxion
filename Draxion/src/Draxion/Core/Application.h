#pragma once
#include "../Core/Core.h"
#include "../Events/Event.h"
#include <memory>
#include "LayerStack.h"

namespace Draxion
{
	class Window;

	class DRX_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
		virtual void OnUpdate();

		static Application& Get();

		void PushLayer(Layer* iLayer);
		void PushOverLay(Layer* iOverLay);
		virtual void OnEvent( Event& e );

		Window& GetWindow();
	private:
		std::unique_ptr<Window> m_Window;
		static Application* s_Instance;
		LayerStack m_Layer_Stack;
	};

	Application* CreateApplication();
}