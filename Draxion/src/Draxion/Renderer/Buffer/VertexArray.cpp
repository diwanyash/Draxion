#include "VertexArray.h"
#include "glad/glad.h"
#include "VertexBuffer.h"

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
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)0);
		glEnableVertexAttribArray(0);

		// COLOR
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
	}


}
