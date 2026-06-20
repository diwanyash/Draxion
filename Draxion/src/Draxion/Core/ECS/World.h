#pragma once
#include "Entity.h"
#include "Component.h"
// #include "Draxion/Debug/Profiler/Profiler.h"
#include "Draxion/Core/Logger.h"
#include <unordered_map>
#include <optional>

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

		uint32_t FindTag( const std::string& tag )
		{
			auto view = View<TagComponent>();
			for ( Entity& entity : view )
			{
				auto& Tag = this->GetComponent<TagComponent>(entity);
				if ( Tag.Tag == tag )
				{
					return entity.GetID();
				}
			}
			return 0;
		}

		/// <summary>
		/// 
		/// make a find entity function that can return a entity based on it's id or TagComponent without having that
		/// entity present on that scope
		/// 
		/// </summary>

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

		inline void SetControlledEntity( const Entity& entity ) { m_Controlled_Entity = entity; }
		inline Entity& GetControlledEntity() { return m_Controlled_Entity; }

		template<typename T>
		bool HasComponent(Entity entity) const;

		template<typename T>
		std::unordered_map<uint32_t, T>& GetStorage();
	private:
		uint32_t m_NextEntityID = 1;
		std::vector<Entity> m_Entities;
		Entity m_Controlled_Entity;
		// <EntityID, Component> ComponentName
		std::unordered_map<uint32_t, TransformComponent> m_Transform;
		std::unordered_map<uint32_t, SpriteComponent> m_Sprite;
		std::unordered_map<uint32_t, TagComponent> m_Tag;
		std::unordered_map<uint32_t, HealthComponent> m_Health;
		std::unordered_map<uint32_t, VelocityComponent> m_Velocity;
		std::unordered_map<uint32_t, AnimationComponent> m_Animation;
		std::unordered_map<uint32_t, ControllableComponent> m_Controllable;
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
	inline bool World::HasComponent<VelocityComponent>(Entity entity) const
	{
		return m_Velocity.find(entity.GetID()) != m_Velocity.end();
	}
	template<>
	inline bool World::HasComponent<AnimationComponent>(Entity entity) const
	{
		return m_Animation.find(entity.GetID()) != m_Animation.end();
	}
	template<>
	inline bool World::HasComponent<ControllableComponent>(Entity entity) const
	{
		return m_Controllable.find(entity.GetID()) != m_Controllable.end();
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
	template<>
	inline std::unordered_map<uint32_t, VelocityComponent>& World::GetStorage()
	{
		return m_Velocity;
	}
	template<>
	inline std::unordered_map<uint32_t, AnimationComponent>& World::GetStorage()
	{
		return m_Animation;
	}
	template<>
	inline std::unordered_map<uint32_t, ControllableComponent>& World::GetStorage()
	{
		return m_Controllable;
	}
}