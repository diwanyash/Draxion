#include "VertexArray.h"
#include "glad/glad.h"
#include "VertexBuffer.h"

// TO_BE DELETED
#include "../../../../Vendor/STB/stb_image.h"	
#include "../../Core/Logger.h"
///////////////
namespace Draxion
{
	VertexArray::VertexArray()
	{
		glCreateVertexArrays( 1, &m_RendererID );
	}
	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}
	void VertexArray::Bind() const
	{
		glBindVertexArray( m_RendererID );
	}
	void VertexArray::Unbind() const
	{
		glBindVertexArray( 0 );
	}

	void VertexArray::AddBuffer(const VertexBuffer& vb) const
	{
		Bind();
		vb.Bind();

		// POS
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)0);
		glEnableVertexAttribArray(0);

		// COLOR
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		// TEXTURE
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);

		///////TO_BE_DELETED//////////////////////////////////////////////////////////////////////

		unsigned int texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
		//glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		int width, height, nrChannels;
		const char* TexPath = "E:/Engine_V1/Draxion/Draxion/src/Draxion/Asset/Images/Neduko.jpg";
		stbi_set_flip_vertically_on_load(true); // Flip on Loading
		unsigned char* TexData = stbi_load(TexPath, &width, &height, &nrChannels, 0);
		if (TexData == NULL)
		{
			LOG_ENGINE_ERROR( "Texture Failed to Load::Path:- " << TexPath );
		}


		glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, TexData );

		glGenerateMipmap( GL_TEXTURE_2D );

		stbi_image_free(TexData);

		//////////////////////////////////////////////////////////////////////////////////////////////

	}


}
