#pragma once
#include "Draxion/Renderer/Texture.h"
#include <glm/glm.hpp>
#include <string>

namespace Draxion
{
	class World;
	class Player
	{
	public:
		Player() = default;
		Player(const std::string& SpriteTextPath, const glm::vec3& pos);

		void OnUpdate( World& world );
		void Draw(float dt);

		glm::vec3& GetPos() { return m_Position; }

		glm::vec4 CalculateTilesUV(int x, int y);
	public:
		enum Face
		{
			Left = 0,
			Right = 1,
			Back = 2,
			Front = 3,
		};
		enum State
		{
			Idle = 0,
			Walking = 1,
			Running = 2,
			Attack = 3
		};
	private:
		Face m_Direction = Face::Front;
		State m_State = State::Walking;
		Draxion::Ref<Texture2D> m_Player_Texture = nullptr;
		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
		std::vector<glm::vec4> m_SpriteUV;
		float FrameTime = 0.0f;
	private:
		// Magic Variables
		float m_Player_Speed = 3.0f;
		glm::vec2 m_Player_Size = { 1.0f,1.0f };
		bool m_Moving = false;
	};
}