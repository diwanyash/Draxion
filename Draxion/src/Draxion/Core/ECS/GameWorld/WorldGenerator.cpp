#include "WorldGenerator.h"

namespace Draxion
{
	void WorldGenerator::Generate(World& world)
	{
		auto Bush_Texture = Texture2D::Create("E:/Engine_V1/Draxion/Sandbox/Assets/Sprites/Bush.png");
		for (int y = 0; y < 15; y++)
		{
			for (int i = 0; i < 15; i++)
			{
				Entity Bush = world.CreateEntity();
				world.AddComponent<TransformComponent>(Bush);
				world.AddComponent<SpriteComponent>(Bush, Bush_Texture);

				auto& transform = world.GetComponent<TransformComponent>(Bush);
				transform.Position.z = 0.4f;
				transform.Position.y = y * 2.0f;
				transform.Position.x = i * 2.0f;
			}
		}
		Entity Tree = world.CreateEntity();
		world.AddComponent<HealthComponent>(Tree,50);
		world.AddComponent<TagComponent>(Tree,"Healthy tree");
		auto& hp = world.GetComponent<HealthComponent>(Tree);
		hp.MaxHealth = 80;	
	}
}
