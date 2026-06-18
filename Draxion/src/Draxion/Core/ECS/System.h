#pragma once
#include "World.h"

namespace Draxion
{
	class RenderSystem
	{
	public:
		static void Render( World& world )
		{
			auto& entities = world.GetEntities();
			for (auto& entity : entities)
			{
				if (!world.HasComponent<Draxion::TransformComponent>(entity))
					continue;
				if (!world.HasComponent<Draxion::SpriteComponent>(entity))
					continue;

				auto& transform = world.GetComponent<Draxion::TransformComponent>(entity);
				auto& sprite = world.GetComponent<Draxion::SpriteComponent>(entity);

				Draxion::Renderer2D::DrawSquare(sprite.Texture, transform.Position, transform.Scale);
			}
		}
	};
}