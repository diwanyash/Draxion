#pragma once
#include <string>
#include <glm/glm.hpp>
#include "Draxion/Renderer/Texture.h"

namespace Draxion
{
	struct TagComponent
	{
		TagComponent(const std::string& tag = "Unknown Entity") : Tag (tag) {}
		std::string Tag;
	};
	struct TransformComponent
	{
		glm::vec3 Position{0.0f};
		glm::vec3 Rotation{0.0f};
		glm::vec3 Scale{1.0f};
	};

	// TODO TilePosiitonComponent
	struct SpriteComponent
	{
		SpriteComponent(const Ref<Texture2D>& tex = nullptr) : Texture(tex) {}
		Ref<Texture2D> Texture;
	};
}