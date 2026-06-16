#include "OpenGLTexture.h"
#include "Logger.h"
#include <glad/glad.h>
#include <stb/stb_image.h>
#include <Draxion/Debug/Profiler/ProfileTimer.h>

namespace Draxion
{
	OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
		:
		m_path(path)
	{
		DX_PROFILE_FUNCTION();

		//////////////////////////STB_IMAGE///////////////////////////////////////////////////////
		int width, height, nrChannels;
		const char* TexPath = path.c_str();
		stbi_set_flip_vertically_on_load(true); // Flip on Loading
		unsigned char* TexData = nullptr;
		{
			DX_PROFILE_SCOPE("Stbi_load::Image_Loading");
			TexData = stbi_load(TexPath, &width, &height, &nrChannels, 0);
		}
		if (TexData == NULL)
		{
			LOG_ENGINE_ERROR("Texture Failed to Load::Path:- " << TexPath);
		}
		m_Width = width;
		m_Height = height;
		//////////////////////////////////////////////////////////////////////////////////////////
		
		GLenum InternalFormat = 0;
		GLenum Format = 0;
		
		if ( nrChannels == 4)
		{
			InternalFormat = GL_RGBA8;
			Format = GL_RGBA;
		}
		else if ( nrChannels == 3 )
		{
			InternalFormat = GL_RGB8;
			Format = GL_RGB;
		}
		
		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, InternalFormat, m_Width, m_Height);
		
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		
		glTextureSubImage2D(
			m_RendererID,
			0,
			0, 0,
			m_Width,
			m_Height,
			Format,
			GL_UNSIGNED_BYTE,
			TexData
		);
		
		glGenerateTextureMipmap(m_RendererID);
		
		stbi_image_free(TexData);
	}
	OpenGLTexture2D::OpenGLTexture2D(const std::string& path, std::pair<int, int> GridPos, std::pair<int, int> GridDim)
		:
		m_path(path)
	{
		DX_PROFILE_FUNCTION();

		//////////////////////////STB_IMAGE///////////////////////////////////////////////////////
		int width, height, nrChannels;
		const char* TexPath = path.c_str();
		stbi_set_flip_vertically_on_load(true); // Flip on Loading
			unsigned char* TexData = nullptr;
		{
			DX_PROFILE_SCOPE("Stbi_load::Image_Loading");
			TexData = stbi_load(TexPath, &width, &height, &nrChannels, 0);
		}
		if (TexData == NULL)
		{
			LOG_ENGINE_ERROR("Texture Failed to Load::Path:- " << TexPath);
		}

		m_Width = width   / GridDim.first;
		m_Height = height / GridDim.second;
		//////////////////////////////////////////////////////////////////////////////////////////

		GLenum InternalFormat = 0;
		GLenum Format = 0;

		if (nrChannels == 4)
		{
			InternalFormat = GL_RGBA8;
			Format = GL_RGBA;
		}
		else if (nrChannels == 3)
		{
			InternalFormat = GL_RGB8;
			Format = GL_RGB;
		}

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, InternalFormat, m_Width, m_Height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureSubImage2D(
			m_RendererID,
			0,
			m_Width * GridPos.first, m_Height * GridPos.second,
			m_Width,
			m_Height,
			Format,
			GL_UNSIGNED_BYTE,
			TexData
		);

		glGenerateTextureMipmap(m_RendererID);

		stbi_image_free(TexData);
	}
	OpenGLTexture2D::~OpenGLTexture2D()
	{
		DX_PROFILE_FUNCTION();

		glDeleteTextures(1, &m_RendererID);
	}
	void OpenGLTexture2D::Bind(unsigned int slot)
	{
		DX_PROFILE_FUNCTION();

		//glActiveTexture(GL_TEXTURE0 + slot);
		glBindTextureUnit(slot, m_RendererID);
	}
}
