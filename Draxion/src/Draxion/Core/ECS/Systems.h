#pragma once
#include "World.h"

namespace Draxion
{
	class RenderSystem
	{
	public:
		static void Render( World& world )
		{
			std::vector<Entity> View = world.View<TransformComponent, SpriteComponent>();
			for (const Entity entity : View)
			{
				auto& transform = world.GetComponent<TransformComponent>(entity);
				auto& sprite = world.GetComponent<SpriteComponent>(entity);

				Renderer2D::DrawSquare(sprite.Texture, transform.Position, transform.Scale);
			}
		}
	};
	class MovementSystem
	{
	public:
		static void Update( World& world, float dt )
		{
			std::vector<Entity> View = world.View<TransformComponent, VelocityComponent>();
			for (const Entity entity : View)
			{
				auto& transform = world.GetComponent<TransformComponent>(entity);
				auto& velocity = world.GetComponent<VelocityComponent>(entity);

				transform.Position.x += velocity.Velocity.x * dt;
				transform.Position.y += velocity.Velocity.y * dt;
			}
		}
	};

	class ControllableSystem
	{
	public:
		static void Update( World& world, float dt )
		{
			std::vector<Entity> View = world.View<ControllableComponent,TransformComponent,VelocityComponent>();

			for ( const Entity entity : View )
			{
				auto& velocity = world.GetComponent<VelocityComponent>(entity);

				bool HasAnimationComponent = world.HasComponent<AnimationComponent>(entity);

				AnimationComponent* animationComponent = nullptr;
				if (HasAnimationComponent)
				{
					animationComponent = &world.GetComponent<AnimationComponent>(entity);
					animationComponent->State = AnimationState::Idle;
				}

				velocity.Velocity = {0.0f,0.0f};
				// TODO Get Speed From Component
				if (Input::IsKeyPressed(DRX_KEY_W))
				{
					velocity.Velocity.y += 3.0f;
					if (HasAnimationComponent)
					{
						animationComponent->Direction = Face::Back;
						animationComponent->State = AnimationState::Walking;
					}
				}

				if (Input::IsKeyPressed(DRX_KEY_S))
				{
					velocity.Velocity.y -= 3.0f;
					if (HasAnimationComponent)
					{
						animationComponent->Direction = Face::Front;
						animationComponent->State = AnimationState::Walking;
					}
				}

				if (Input::IsKeyPressed(DRX_KEY_A))
				{
					velocity.Velocity.x -= 3.0f;
					if (HasAnimationComponent)
					{
						animationComponent->Direction = Face::Left;
						animationComponent->State = AnimationState::Walking;
					}
				}

				if (Input::IsKeyPressed(DRX_KEY_D))
				{
					velocity.Velocity.x += 3.0f;
					if (HasAnimationComponent)
					{
						animationComponent->Direction = Face::Right;
						animationComponent->State = AnimationState::Walking;
					}
				}
			}
		}
	};

	class AnimationSystem
	{
	public:
		static void AdvanceFrame( World& world, float dt )
		{
			std::vector<Entity> View = world.View<AnimationComponent, SpriteComponent, TransformComponent>();

			for ( const Entity entity : View)
			{

			}
		}
	};
}