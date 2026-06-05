#pragma once
#include "../../Core/Layer.h"
#include "../Core.h"
#include "../../Events/KeyEvent.h"
#include "../../Events/MouseEvents.h"
#include "../../Events/ApplicationEvent.h"


namespace Draxion
{
	class DRX_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer()
			:
			Layer("ImGui_Layer")
		{}

		void OnAttach() override;
		void OnDetach() override;
		void OnEvent( Event& e ) override;
		void OnImGuiRender() override;

		void Begin();
		void End();
	};
}