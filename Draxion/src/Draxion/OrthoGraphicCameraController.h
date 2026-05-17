#pragma once
#include "Draxion/Renderer/OrthoGraphicCamera.h"
#include "Draxion/Events/Event.h"
#include "Draxion/Core/Util/Timestamp.h"

namespace Draxion
{
	class OrthoGraphicCameraController
	{
	public:
		OrthoGraphicCameraController( float aspectRatio, bool rotation = false);

		void OnUpdate( TimeStamp dt );
		void OnEvent( Event& e );
		OrthoGraphicCamera& GetCamera() { return m_Camera; }
	private:
		float m_AspectRatio;
		float m_Zoom_Ratio = 1.0f;
		////////////Camera////////////////////
		glm::vec3 Cam_Pos = { 0.0f, 0.0f, 0.0f };
		float Cam_Rot = 0.0f;
		float Cam_Move_Speed = 5.0f;
		float Cam_Rotation_Speed = 180.0f;
		//////////////////////////////////////
		bool m_IsRotationOn;
		OrthoGraphicCamera m_Camera;
	};
}