#pragma once
#include "Draxion/Renderer/Texture.h"
#include <string>

namespace Draxion
{
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(const std::string& path);

		~OpenGLTexture2D() override;

		unsigned int GetWidth() const override { return m_Width; }
		unsigned int GetHeight() const override { return m_Height; }

		void Bind(unsigned int slot = 0) override;
	private:
		std::string  m_path;
		unsigned int m_Width;
		unsigned int m_Height;
		unsigned int m_RendererID;
	};
}