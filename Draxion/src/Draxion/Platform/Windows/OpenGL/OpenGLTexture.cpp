#include "OpenGLTexture.h"
#include "Logger.h"
#include <glad/glad.h>
#include <stb/stb_image.h>

namespace Draxion
{
	OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
		:
		m_path(path)
	{
		//////////////////////////STB_IMAGE///////////////////////////////////////////////////////
		int width, height, nrChannels;
		const char* TexPath = path.c_str();
		stbi_set_flip_vertically_on_load(true); // Flip on Loading
		unsigned char* TexData = stbi_load(TexPath, &width, &height, &nrChannels, 0);
		if (TexData == NULL)
		{
			LOG_ENGINE_ERROR("Texture Failed to Load::Path:- " << TexPath);
		}
		m_Width = width;
		m_Height = height;
		//////////////////////////////////////////////////////////////////////////////////////////

		glCreateTextures(GL_TEXTURE_2D,1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, GL_RGBA8, m_Width, m_Height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
		//glTexParameteri( m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


		// change this if error occurs
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, TexData);

		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(TexData);
	}
	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_RendererID);
	}
	void OpenGLTexture2D::Bind(unsigned int slot)
	{
		glBindTextureUnit(0, m_RendererID);
	}
}
