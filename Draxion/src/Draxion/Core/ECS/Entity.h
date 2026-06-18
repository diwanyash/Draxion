#pragma once
#include <cstdint>
#include <string>
#include <glm/glm.hpp>

namespace Draxion
{
	class World;

	class Entity
	{
	public:
		Entity() = default;
		Entity(uint32_t id, World* world);

		inline uint32_t GetID() const { return m_ID; }
		explicit operator bool() const { return m_ID != 0; }
	private:
		uint32_t m_ID = 0;
		World* m_World = nullptr;
	};
}