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
		void OnUpdateOnly();
		void OnEvent( Event& e );
		
		inline void SetZoomRatio(const float ZoomRatio) { m_Zoom_Ratio = ZoomRatio; RecalculateZoom(); }
		
		inline const glm::vec3 GetPos() const { return Cam_Pos; }
		inline const void SetPos( const glm::vec3& Pos ) { Cam_Pos = Pos; }

		inline const float GetZoomRatio() const { return m_Zoom_Ratio; }
		inline const float GetAspectRatio() const { return m_AspectRatio; }
		OrthoGraphicCamera& GetCamera() { return m_Camera; }
	private:
		float m_AspectRatio;
		float m_Zoom_Ratio = 1.0f;
		////////////Camera////////////////////
		glm::vec3 Cam_Pos = { 0.0f, 0.0f, 0.0f };
		float Cam_Rot = 0.0f;
		float Cam_Move_Speed = 1.0f;
		float Cam_Rotation_Speed = 180.0f;
		//////////////////////////////////////
		bool m_IsRotationOn;
		OrthoGraphicCamera m_Camera;
	private:
		void RecalculateZoom();
	};
}