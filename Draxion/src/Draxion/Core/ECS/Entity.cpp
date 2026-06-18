#include "Entity.h"
#include "World.h"

namespace Draxion
{
	Entity::Entity(uint32_t id, World* world)
		:
		m_ID(id),
		m_World(world)
	{}
}
