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
		OrthoGraphicCamera m_Camera = { -1.2f, 1.2f, -0.9f, 0.9f };
		glm::vec3 Cam_Pos = m_Camera.GetPosition();
		std::shared_ptr<Shader>  m_Shader = nullptr;
		std::shared_ptr<Shader>  m_ShaderInv = nullptr;
	};
}