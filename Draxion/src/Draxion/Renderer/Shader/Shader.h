#pragma once
#include "../../Core/Core.h"

namespace Draxion
{
	class DRX_API Shader
	{
	public:
		Shader( const char* vertexShader, const char* fragmentShader );
		~Shader();

		void Bind() const;
		void Unbind() const;
	private:
		unsigned int m_RendererID;
	};
}