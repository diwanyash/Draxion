#pragma once
#include "../../Core/Core.h"
#include <glm/glm.hpp>
#include <string>

namespace Draxion
{
	class DRX_API Shader
	{
	public:
		virtual ~Shader() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static Shader* Create( const char* vertexShader, const char* fragmentShader );
	};
}