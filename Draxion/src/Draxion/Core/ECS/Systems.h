#pragma once
#include "World.h"

namespace Draxion
{
	class RenderSystem
	{
	public:
		static void Render( World& world )
		{
			std::vector<Entity> entities = world.View<TransformComponent, SpriteComponent>();
			for (const Entity entity : entities)
			{
				auto& transform = world.GetComponent<TransformComponent>(entity);
				auto& sprite = world.GetComponent<SpriteComponent>(entity);

				Renderer2D::DrawSquare(sprite.Texture, transform.Position, transform.Scale);
			}
		}
	};
}