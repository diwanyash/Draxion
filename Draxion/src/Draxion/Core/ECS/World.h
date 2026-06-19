#pragma once
#include "Entity.h"
#include "Component.h"
#include <unordered_map>

namespace Draxion
{
	class World
	{
	public:
		Entity CreateEntity();
		void DestroyEntity(Entity entity);

		template<typename T, typename... Args>
		T& AddComponent(Entity entity,Args... args)
		{
			auto& storage = GetStorage<T>();
			return storage.emplace(
				entity.GetID(),
				T(std::forward<Args>(args)...)
			).first->second;
		}
		template<typename T>
		void RemoveComponent(Entity entity)
		{
			auto& storage = GetStorage<T>();
			storage.erase(entity.GetID());
		}
		template<typename T>
		T& GetComponent(Entity entity)
		{
			auto& storage = GetStorage<T>();
			return storage.at(entity.GetID());
		}

		template<typename... Components>
		std::vector<Entity> View() const
		{
			std::vector<Entity> OutVec;

			for (const Entity& entity : m_Entities)
			{
				if ((HasComponent<Components>(entity)&& ...))
				{
					OutVec.push_back(entity);
				}
			}
			return OutVec;
		}

		inline std::vector<Entity>& GetEntities() { return m_Entities; };

		template<typename T>
		bool HasComponent(Entity entity) const;

		template<typename T>
		std::unordered_map<uint32_t, T>& GetStorage();
	private:
		uint32_t m_NextEntityID = 1;
		std::vector<Entity> m_Entities;
		// <EntityID, Component> ComponentName
		std::unordered_map<uint32_t, TransformComponent> m_Transform;
		std::unordered_map<uint32_t, SpriteComponent> m_Sprite;
		std::unordered_map<uint32_t, TagComponent> m_Tag;
		std::unordered_map<uint32_t, HealthComponent> m_Health;
	};
	template<>
	inline bool World::HasComponent<TransformComponent>(Entity entity) const
	{
		return m_Transform.find(entity.GetID()) != m_Transform.end();
	}
	template<>
	inline bool World::HasComponent<SpriteComponent>(Entity entity) const
	{
		return m_Sprite.find(entity.GetID()) != m_Sprite.end();
	}
	template<>
	inline bool World::HasComponent<TagComponent>(Entity entity) const
	{
		return m_Tag.find(entity.GetID()) != m_Tag.end();
	}
	template<>
	inline bool World::HasComponent<HealthComponent>(Entity entity) const
	{
		return m_Health.find(entity.GetID()) != m_Health.end();
	}
	template<>
	inline std::unordered_map<uint32_t, TransformComponent>& World::GetStorage()
	{
		return m_Transform;
	}
	template<>
	inline std::unordered_map<uint32_t, SpriteComponent>& World::GetStorage()
	{
		return m_Sprite;
	}
	template<>
	inline std::unordered_map<uint32_t, TagComponent>& World::GetStorage()
	{
		return m_Tag;
	}
	template<>
	inline std::unordered_map<uint32_t, HealthComponent>& World::GetStorage()
	{
		return m_Health;
	}
}