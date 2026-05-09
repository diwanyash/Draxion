#pragma once

namespace Draxion
{
	enum class RendererAPI
	{
		None = 0,
		OpenGL = 1
	};

	class Renderer
	{
	public:
		inline static RendererAPI GetAPI() { return m_rendererAPI; }
	private:
		static RendererAPI m_rendererAPI;
	};
}