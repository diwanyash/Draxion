#pragma once
#include "DraxionMain.h"

namespace Draxion
{
	class ExampleLayer : public Layer
	{
	public:
		ExampleLayer()
			:
			Layer("Example_Layer")
		{}

		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate() override;
		void OnImGuiRender() override;
		void OnEvent(Event& e) override;
	private:
		std::shared_ptr<VertexArray> m_VAO;
		const Shader*  m_Shader = nullptr;
		const Shader*  m_ShaderInv = nullptr;
	};
}