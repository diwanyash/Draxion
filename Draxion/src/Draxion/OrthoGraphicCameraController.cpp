#include "OrthoGraphicCameraController.h"
#include "Draxion/Input/KeyCodes.h"
#include "Draxion/Input/Input.h"
#include "Draxion/Events/EventDispatcher.h"
#include "Draxion/Events/ApplicationEvent.h"
#include "Draxion/Events/MouseEvents.h"

namespace Draxion
{
	OrthoGraphicCameraController::OrthoGraphicCameraController(float aspectRatio, bool rotation)
		:
		m_AspectRatio(aspectRatio),
		m_Camera( -m_AspectRatio * m_Zoom_Ratio, m_AspectRatio * m_Zoom_Ratio, -m_Zoom_Ratio, m_Zoom_Ratio ),
		m_IsRotationOn(rotation)
	{
		
	}
	void OrthoGraphicCameraController::OnUpdate( TimeStamp dt )
	{
		if (Input::IsKeyPressed(DRX_KEY_W))
		{
			Cam_Pos.y += Cam_Move_Speed * dt;
		}
		if (Input::IsKeyPressed(DRX_KEY_S))
		{
			Cam_Pos.y -= Cam_Move_Speed * dt;
		}
		if (Input::IsKeyPressed(DRX_KEY_D))
		{
			Cam_Pos.x += Cam_Move_Speed * dt;
		}
		if (Input::IsKeyPressed(DRX_KEY_A))
		{
			Cam_Pos.x -= Cam_Move_Speed * dt;
		}
		if (Input::IsKeyPressed(DRX_KEY_Q))
		{
			Cam_Rot -= Cam_Rotation_Speed * dt;
		}
		if (Input::IsKeyPressed(DRX_KEY_E))
		{
			Cam_Rot += Cam_Rotation_Speed * dt;
		}

		m_Camera.SetPosition( Cam_Pos );
		
		if( m_IsRotationOn )
		m_Camera.SetRotation( Cam_Rot );

		Cam_Move_Speed = m_Zoom_Ratio;
	}
	void OrthoGraphicCameraController::OnEvent( Event& e )
	{
		EventDispatcher d(e);

		d.Dispatch<MouseScrolledEvent>([&](MouseScrolledEvent& e)
		{
			m_Zoom_Ratio -= e.GetYOffset() * 0.05f;
			m_Zoom_Ratio = std::max(m_Zoom_Ratio, 0.01f);
			m_Camera.SetProjection(-m_AspectRatio * m_Zoom_Ratio, m_AspectRatio * m_Zoom_Ratio,
				-m_Zoom_Ratio, m_Zoom_Ratio);

			return false;
		});
	}
}