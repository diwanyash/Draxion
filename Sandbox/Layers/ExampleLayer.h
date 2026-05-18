#pragma once
#include "DraxionMain.h"

namespace Draxion
{
	class ExampleLayer : public Layer
	{
	public:
		ExampleLayer()
			:
			Layer("Example_Layer"),
			m_CameraController( 1280.0f / 720.0f)
		{}

		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate(float delta_time) override;
		void OnImGuiRender() override;
		void OnEvent(Event& e) override;
	private:
		Ref<VertexArray> m_VAO;
		OrthoGraphicCameraController m_CameraController;
		///////////Camera/////////////////////
		glm::vec3 m_SquarePosition = { 1.0f,1.0f,1.0f };
		//////////////////////////////////////
		Ref<Shader>  m_Shader = nullptr;
		Ref<Shader>  m_ShaderInv = nullptr;
		Ref<Texture2D> m_Neduko_SanGoku;
		Ref<Texture2D> m_Pikachuuu;
		////////////////////TEST/////////////
		glm::vec3 pos2 = { 0.60f,0.25f,0.0f };
		float Occu = 1.0f;
	};
}