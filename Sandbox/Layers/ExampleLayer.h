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
		void OnUpdate(float delta_time) override;
		void OnImGuiRender() override;
		void OnEvent(Event& e) override;
	private:
		Ref<VertexArray> m_VAO;
		OrthoGraphicCamera m_Camera = { -1.2f, 1.2f, -0.9f, 0.9f };
		///////////Camera/////////////////////
		glm::vec3 Cam_Pos = m_Camera.GetPosition();
		glm::vec3 m_SquarePosition = { 1.0f,1.0f,1.0f };
		float Cam_Rot = 0.0f;
		float Cam_Move_Speed = 1.0f;
		float Cam_Rotation_Speed = 180.0f;
		float TexScaler = 1.0f;
		//////////////////////////////////////
		Ref<Shader>  m_Shader = nullptr;
		Ref<Shader>  m_ShaderInv = nullptr;
		///////////TEST////////////////////
		int x1 = 20;
		int y1 = 20;
	};
}