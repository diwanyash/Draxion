#pragma once
#include <glm/glm.hpp>

namespace Draxion
{
	class SpriteSheet
	{
	public:
		SpriteSheet( const glm::ivec2& spriteCoords );
		const glm::vec4& GetFrameUV(int x, int y) const;
	private:
		glm::vec4 m_FrameUV = { 1.0f, 1.0f, 1.0f, 1.0f };
		glm::ivec2 m_FrameCoord = { 1, 1 };
	};
}