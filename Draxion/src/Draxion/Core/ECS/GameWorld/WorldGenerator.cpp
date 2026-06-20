#include "WorldGenerator.h"
#include "Draxion/Core/Util/RandomGen.h"

namespace Draxion
{
	void WorldGenerator::Generate(World& world)
	{
		auto Bush_Texture = Texture2D::Create("E:/Engine_V1/Draxion/Sandbox/Assets/Sprites/Bush.png");

		 auto Player = world.CreateEntity();
		 world.AddComponent<TransformComponent>(Player, glm::vec3{1.0f,1.0f,1.0f});
		 world.AddComponent<ControllableComponent>(Player);
		 world.AddComponent<AnimationComponent>(Player);
		 world.AddComponent<TagComponent>(Player,"Joe");
		 world.AddComponent<VelocityComponent>(Player);
		 world.SetControlledEntity(Player); // Set Player the Controlled Entity

		for (int y = 0; y < 15; y++)
		{
			for (int i = 0; i < 15; i++)
			{
				Entity Bush = world.CreateEntity();
				world.AddComponent<TransformComponent>(Bush);
				world.AddComponent<SpriteComponent>(Bush, Bush_Texture);
				world.AddComponent<VelocityComponent>(Bush, glm::vec2{RandomGen::Get<float>(-1.0f,1.0f),RandomGen::Get<float>(-1.0f,1.0f) });

				auto& transform = world.GetComponent<TransformComponent>(Bush);
				transform.Position.z = 0.4f;
				transform.Position.y = y * 2.0f;
				transform.Position.x = i * 2.0f;
			}
		}
	}
}
