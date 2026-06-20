#pragma once
#include <string>
#include <glm/glm.hpp>
#include "Draxion/Renderer/Texture.h"
#include <Draxion/Renderer/Sprite/SpriteSheet.h>

namespace Draxion
{
	//////////////-ENUMERATION-/////////////////////////////////////////////
	enum class Face
	{
		Left = 0,
		Right = 1,
		Back = 2,
		Front = 3,
	};
	enum class AnimationState
	{
		Idle = 0,
		Walking = 1,
		Running = 2,
		Attack = 3
	};

	//////////////-COMPONENTS-/////////////////////////////////////////////
	struct TagComponent
	{
		TagComponent(const std::string& tag = "Unknown Entity") : Tag (tag) {}
		std::string Tag;
	};
	struct TransformComponent
	{
		TransformComponent(const glm::vec3& position = {0.0f,0.0f,0.0f},const glm::vec2& scale = {1.0f,1.0}, const glm::vec3& rotation = { 0.0f,0.0f,0.0f })
			:
			Position(position),
			Scale(scale),
			Rotation(rotation)
		{}
		glm::vec3 Position;
		glm::vec2 Scale;
		glm::vec3 Rotation;
	};

	// TODO TilePosiitonComponent
	struct SpriteComponent
	{
		SpriteComponent( const Ref<Texture2D>& tex = nullptr, const glm::ivec2& spriteCoords = { 1,1 } )
			: Texture(tex), Sprite(spriteCoords) {}
		Ref<Texture2D> Texture;
		SpriteSheet Sprite;
	};

	struct HealthComponent
	{
		HealthComponent(const int maxhealth = 0) : MaxHealth(maxhealth) { CurHealth = maxhealth; }
		int CurHealth = 0;
		int MaxHealth;
	};

	struct VelocityComponent
	{
		VelocityComponent(const glm::vec2 velocity = { 0.0f,0.0f }) : Velocity(velocity) {}
		glm::vec2 Velocity;
	};

	struct ControllableComponent
	{
		ControllableComponent() = default;
		glm::vec2 Velocity = {0.0f,0.0f};
	};

	struct AnimationComponent
	{
		AnimationState State = AnimationState::Idle;
		Face Direction = Face::Front;

		float Timer = 0.0f;
		uint32_t CurruntFrame = 0;
	};
}