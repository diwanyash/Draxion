#include "World.h"

namespace Draxion
{
    Entity World::CreateEntity()
    {
        Entity entity(m_NextEntityID++, this);

        m_Entities.push_back( entity );

        return entity;
    }
    void World::DestroyEntity(Entity entity)
    {
        uint32_t id = entity.GetID();

        m_Transform.erase(id);
        m_Sprite.erase(id);
        m_Tag.erase(id);

        auto it = std::find_if(m_Entities.begin(), m_Entities.end(),
            [id](const Entity& e)
        { 
            return e.GetID() == id;
        });

        if (it != m_Entities.end())
            m_Entities.erase(it);

        m_NextEntityID--;
    }
}
