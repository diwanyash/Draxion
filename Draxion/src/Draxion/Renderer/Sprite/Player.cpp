#include "Player.h"
#include "Draxion/Input/Input.h"
#include "Draxion/Input/KeyCodes.h"
#include "Draxion/Renderer/Renderer2D.h"
#include <Logger.h>
#include <Draxion/Debug/Profiler/ProfileTimer.h>

namespace Draxion
{
	Player::Player(const std::string& SpriteTextPath, const glm::vec3& pos)
		:
		m_Position(pos)
	{
		DX_PROFILE_FUNCTION();

		m_Player_Texture = Texture2D::Create(SpriteTextPath);

		for ( int y = 0; y < 4; y++)
		{
			for (int x = 0; x < 4; x++)
			{
				auto result = CalculateTilesUV(x, y);
				m_SpriteUV.push_back(glm::vec4{ result.x,result.y,result.z,result.w });
			}
		}
		for (int y = 4; y < 8; y++)
		{
			for (int x = 0; x < 2; x++)
			{
				auto result = CalculateTilesUV(x, y);
				m_SpriteUV.push_back(glm::vec4{result.x,result.y,result.z,result.w});
			}
		}

		LOG_ENGINE_WARN("Delta Time in Player Draw : " << m_Player_Size.x << " | " << m_Player_Size.y);
	}

	void Player::OnUpdate(float dt)
	{
		DX_PROFILE_FUNCTION();

		m_Moving = false;

		if ( Input::IsKeyPressed( DRX_KEY_W ))
		{
			m_Position.y += m_Player_Speed * dt;
			m_Direction = Face::Back;
			m_Moving = true;
		}
		else if ( Input::IsKeyPressed( DRX_KEY_S ))
		{
			m_Position.y -= m_Player_Speed * dt;
			m_Direction = Face::Front;
			m_Moving = true;
		}


		if ( Input::IsKeyPressed(DRX_KEY_A))
		{
			m_Position.x -= m_Player_Speed * dt;
			m_Direction = Face::Left;
			m_Moving = true;
		}
		else if ( Input::IsKeyPressed( DRX_KEY_D ))
		{
			m_Position.x += m_Player_Speed * dt;
			m_Direction = Face::Right;
			m_Moving = true;
		}

		m_State = m_Moving ? State::Walking : State::Idle;
	}
	void Player::Draw(float dt)
	{
		DX_PROFILE_FUNCTION();

		FrameTime += dt;

		// WALKING
		if( m_State == State::Walking && FrameTime < 0.25f )
		{
			Renderer2D::DrawSquare(m_Player_Texture, m_Position , m_SpriteUV[0 + (4 * m_Direction)], m_Player_Size);
		}
		else if(m_State == State::Walking && FrameTime < 0.5f )
		{
			Renderer2D::DrawSquare(m_Player_Texture, m_Position, m_SpriteUV[1 + (4 * m_Direction)], m_Player_Size);
		}
		else if(m_State == State::Walking && FrameTime < 0.75f )
		{
			Renderer2D::DrawSquare(m_Player_Texture, m_Position, m_SpriteUV[2 + (4 * m_Direction)], m_Player_Size);
		}
		else if(m_State == State::Walking && FrameTime < 1.0f )
		{
			Renderer2D::DrawSquare(m_Player_Texture, m_Position, m_SpriteUV[3 + (4 * m_Direction)], m_Player_Size);
		}

		// IDLE
		if(m_State == State::Idle && FrameTime < 0.5f)
		{
			Renderer2D::DrawSquare(m_Player_Texture, m_Position, m_SpriteUV[16 + (2 * m_Direction)], m_Player_Size);
		}
		else if (m_State == State::Idle && FrameTime < 1.0f)
		{
			Renderer2D::DrawSquare(m_Player_Texture, m_Position, m_SpriteUV[17 + (2 * m_Direction)], m_Player_Size);
		}

		if( FrameTime >= 1.0f )
		FrameTime = 0.0f;
	}

	glm::vec4 Player::CalculateTilesUV(int x, int y)
	{
		DX_PROFILE_FUNCTION();

		float TileWidth = 1.0f / 4.0f;
		float TileHeight = 1.0f / 8.0f;

		float u0 = (float)x * TileWidth;
		float v0 = (float)y * TileHeight;

		float u1 = u0 + TileWidth;
		float v1 = v0 + TileHeight;

		return glm::vec4(u0, v0, u1, v1);
	}
}