#include "Player.h"
#include "Draxion/Input/Input.h"
#include "Draxion/Input/KeyCodes.h"
#include "Draxion/Renderer/Renderer2D.h"
#include <Logger.h>

namespace Draxion
{
	Player::Player(const std::string& SpriteTextPath, const glm::vec3& pos)
		:
		m_Position(pos)
	{
		m_Player_Texture = Texture2D::Create(SpriteTextPath);

		int SpriteUV_Size = 16 * 4;
		int Index = 0;

		for ( int y = 0; y < 4; y++)
		{
			for (int x = 0; x < 4; x++)
			{
				auto result = CalculateTilesUV( x, y );
				m_SpriteUV[0 + Index] = result.x;
				m_SpriteUV[1 + Index] = result.y;
				m_SpriteUV[2 + Index] = result.z;
				m_SpriteUV[3 + Index] = result.w;
				Index += 4;
			}
		}

		LOG_ENGINE_WARN("Delta Time in Player Draw : " << m_Player_Size.x << " | " << m_Player_Size.y);
	}

	void Player::OnUpdate(float dt)
	{
		if ( Input::IsKeyPressed( DRX_KEY_W ))
		{
			m_Position.y += m_Player_Speed * dt;
			m_Direction = Face::Back;
		}
		else if ( Input::IsKeyPressed(DRX_KEY_A))
		{
			m_Position.x -= m_Player_Speed * dt;
			m_Direction = Face::Left;
		}
		else if ( Input::IsKeyPressed( DRX_KEY_S ))
		{
			m_Position.y -= m_Player_Speed * dt;
			m_Direction = Face::Front;
		}
		else if ( Input::IsKeyPressed( DRX_KEY_D ))
		{
			m_Position.x += m_Player_Speed * dt;
			m_Direction = Face::Right;
		}
	}
	void Player::Draw(float dt)
	{
		FrameTime += dt;
		if( FrameTime < 0.25f )
		{
			Renderer2D::DrawSquare(m_Player_Texture, m_Position, { m_SpriteUV[0 + (16 * m_Direction)],m_SpriteUV[1 + (16 * m_Direction)],m_SpriteUV[2 + (16 * m_Direction)],m_SpriteUV[3 + (16 * m_Direction)],}, m_Player_Size);
		}
		else if( FrameTime < 0.5f )
		{
			Renderer2D::DrawSquare(m_Player_Texture, m_Position, { m_SpriteUV[4 + (16 * m_Direction)],m_SpriteUV[5 + (16 * m_Direction)],m_SpriteUV[6 + (16 * m_Direction)],m_SpriteUV[7 + (16 * m_Direction)], }, m_Player_Size);
		}
		else if( FrameTime < 0.75f )
		{
			Renderer2D::DrawSquare(m_Player_Texture, m_Position, { m_SpriteUV[8 + (16 * m_Direction)],m_SpriteUV[9 + (16 * m_Direction)],m_SpriteUV[10 + (16 * m_Direction)],m_SpriteUV[11 + (16 * m_Direction)], }, m_Player_Size);
		}
		else if( FrameTime < 1.0f )
		{
			Renderer2D::DrawSquare(m_Player_Texture, m_Position, { m_SpriteUV[12 + (16 * m_Direction)],m_SpriteUV[13 + (16 * m_Direction)],m_SpriteUV[14 + (16 * m_Direction)],m_SpriteUV[15 + (16 * m_Direction)], }, m_Player_Size);
		}
		else
		{
			FrameTime = 0.0f;
		}
	}

	glm::vec4 Player::CalculateTilesUV(int x, int y)
	{
		float TileWidth = 1.0f / 4.0f;
		float TileHeight = 1.0f / 4.0f;

		float u0 = (float)x * TileWidth;
		float v0 = (float)y * TileHeight;

		float u1 = u0 + TileWidth;
		float v1 = v0 + TileHeight;

		return glm::vec4(u0, v0, u1, v1);
	}
}