#pragma once
#include "../../Core/Core.h"
#include <glm/glm.hpp>
#include <string>

namespace Draxion
{
	class DRX_API Shader
	{
	public:
		Shader( const char* vertexShader, const char* fragmentShader );
		~Shader();

		void Bind() const;
		void Unbind() const;
		void UploadUniformMat4(const std::string& name,const glm::mat4& matrix );
	private:
		unsigned int m_RendererID;
	};
}