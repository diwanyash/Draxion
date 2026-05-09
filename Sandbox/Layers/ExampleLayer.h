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
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<VertexBuffer> m_VBO;
		std::unique_ptr<IndexBuffer> m_EBO;
		const Shader*  m_Shader = nullptr;
	};
}