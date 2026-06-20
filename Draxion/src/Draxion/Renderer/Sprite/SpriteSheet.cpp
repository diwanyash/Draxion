#include "SpriteSheet.h"
#include <Draxion/Debug/Profiler/ProfileTimer.h>

namespace Draxion
{
	SpriteSheet::SpriteSheet(const glm::ivec2& spriteCoords)
		:
		m_FrameCoord(spriteCoords)
	{}
	const glm::vec4& SpriteSheet::GetFrameUV(int x, int y) const
	{
		DX_PROFILE_FUNCTION();

		float TileWidth = 1.0f / (float)m_FrameCoord.x;
		float TileHeight = 1.0f / (float)m_FrameCoord.y;

		float u0 = (float)x * TileWidth;
		float v0 = (float)y * TileHeight;

		float u1 = u0 + TileWidth;
		float v1 = v0 + TileHeight;

		return glm::vec4(u0, v0, u1, v1);
	}
}
