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

		virtual void SetInt(const std::string& name, int value) = 0;
		virtual void SetIntArray(const std::string& name, int* values, unsigned int count) = 0;
		virtual void SetInt2(const std::string& name, glm::ivec2 ivec) = 0;
		virtual void SetInt3(const std::string& name, glm::ivec3 ivec) = 0;
		virtual void SetInt4(const std::string& name, glm::ivec4 ivec) = 0;
																	   
		virtual void SetFloat(const std::string& name, float value) = 0;
		virtual void SetFloat2(const std::string& name, glm::vec2 vec) = 0;
		virtual void SetFloat3(const std::string& name, glm::vec3 vec) = 0;
		virtual void SetFloat4(const std::string& name, glm::vec4 vec) = 0;
																	   
		virtual void SetMat3(const std::string& name, glm::mat3 mat) = 0;
		virtual void SetMat4(const std::string& name, glm::mat4 mat) = 0;


		static Ref<Shader> Create( const char* vertexShader, const char* fragmentShader );
	};
}