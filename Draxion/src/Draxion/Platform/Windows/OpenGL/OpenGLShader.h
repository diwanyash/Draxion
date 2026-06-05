#pragma once
#include "Draxion/Renderer/Shader/Shader.h"

namespace Draxion
{
	class DRX_API OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const char* vertexShader, const char* fragmentShader);
		~OpenGLShader() override;

		void Bind() const override;
		void Unbind() const override;

		void SetInt(const std::string& name, int value) override; 
		void SetIntArray(const std::string& name, int* values, unsigned int count) override;
		void SetInt2(const std::string& name, glm::ivec2 ivec) override; 
		void SetInt3(const std::string& name, glm::ivec3 ivec) override; 
		void SetInt4(const std::string& name, glm::ivec4 ivec) override; 
															   
		void SetFloat(const std::string& name, float value) override;   
		void SetFloat2(const std::string& name, glm::vec2 vec) override; 
		void SetFloat3(const std::string& name, glm::vec3 vec) override; 
		void SetFloat4(const std::string& name, glm::vec4 vec) override; 
															   
		void SetMat3(const std::string& name, glm::mat3 mat) override; 
		void SetMat4(const std::string& name, glm::mat4 mat) override; 

		void UploadUniformInt(const std::string& name, const int value);
		void UploadUniformIntArray( const std::string& name, int* values, unsigned int count );
		void UploadUniformInt2(const std::string& name, const glm::ivec2 ivec);
		void UploadUniformInt3(const std::string& name, const glm::ivec3 ivec);
		void UploadUniformInt4(const std::string& name, const glm::ivec4 ivec);

		void UploadUniformFloat(const std::string& name, const float value);
		void UploadUniformFloat2(const std::string& name, const glm::vec2& vec);
		void UploadUniformFloat3(const std::string& name, const glm::vec3& vec);
		void UploadUniformFloat4(const std::string& name, const glm::vec4& vec);

		void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
	private:
		unsigned int m_RendererID;
	};
}