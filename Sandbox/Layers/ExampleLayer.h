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
		void OnEvent(Event& e) override;
	private:
		const VertexArray*  m_VAO = nullptr;
		const VertexBuffer* m_VBO = nullptr;
		const IndexBuffer*  m_EBO = nullptr;
		const Shader*  m_Shader = nullptr;
	};
}