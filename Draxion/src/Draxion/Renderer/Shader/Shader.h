#pragma once
#include <string>
#include "../../Core/Core.h"

namespace Draxion
{
	class DRX_API Shader
	{
	public:
		Shader( const std::string& vertexShader, const std::string& fragmentShader );
		~Shader();

		void Bind() const;
		void Unbind() const;
	private:
		unsigned int m_RendererID;
	};
}