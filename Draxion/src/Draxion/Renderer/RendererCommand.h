#pragma once

namespace Draxion
{
	class RendererCommand
	{
	public:
		static void Init();

		static void SetClearColor( float r, float g, float b, float a );
		static void Clear();
		static void Draw();
	private:
	};
}