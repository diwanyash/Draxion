#pragma once
#include "Core.h"
#include "../Events/Event.h"
#include "LayerStack.h"
#include <memory>
#include "Layer/ImGuiLayer.h"

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
		void PopLayer(Layer* iLayer);
		void PopOverLay(Layer* iOverLay);

		virtual void OnEvent( Event& e );

		Window& GetWindow();
	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		static Application* s_Instance;
		LayerStack m_Layer_Stack;
	};

	Application* CreateApplication();
}