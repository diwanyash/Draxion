#pragma once
#include "Draxion/Renderer/OrthoGraphicCamera.h"
#include "Draxion/Renderer/Texture.h"

namespace Draxion
{
	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();
		static void OnWindowResize(unsigned int Width, unsigned int Height);
		static void BeginScene(OrthoGraphicCamera& camera);

		static void DrawSquare(const glm::vec2& Position, const glm::vec2& Size, const glm::vec4& Color = { 1.0f,1.0f,1.0f,1.0f });
		static void DrawSquare(const glm::vec3& Position, const glm::vec2& Size, const glm::vec4& Color = { 1.0f,1.0f,1.0f,1.0f });

		static void DrawSquare(const Ref<Texture2D>& texture,const glm::vec2& Position, const glm::vec2& Size, const glm::vec4& Color = { 1.0f,1.0f,1.0f,1.0f })
		{
			DrawSquare(texture, { Position.x, Position.y, 0.0f }, Size, Color);
		}
		static void DrawSquare(const Ref<Texture2D>& texture,const glm::vec3& Position, const glm::vec2& Size, const glm::vec4& Color = { 1.0f,1.0f,1.0f,1.0f });
		
		static void DrawSquare(const Ref<Texture2D>& texture,const glm::vec2& Position, const glm::vec4& UV, const glm::vec2& Size, const glm::vec4& Color = { 1.0f,1.0f,1.0f,1.0f });
		static void DrawSquare(const Ref<Texture2D>& texture,const glm::vec3& Position, const glm::vec4& UV, const glm::vec2& Size, const glm::vec4& Color = { 1.0f,1.0f,1.0f,1.0f });
		
		//static void DrawSquare(const glm::vec3& Position, const glm::vec2& Size, const glm::vec4& color);
		static void SetGrid(const glm::ivec2& value);

		static void EndScene();
		static void ResetStates();
	public:
		struct Statistics
		{
			uint32_t DrawCalls = 0;
			uint32_t SquareCount = 0;

			uint32_t GetTotalVertexCount() { return SquareCount * 4; }
			uint32_t GetTotalIndexCount() { return SquareCount * 6; }
		};
	public:
		static Statistics GetStates();
	private:
		static void FlushAndReset();
		static void Flush();
	};
}