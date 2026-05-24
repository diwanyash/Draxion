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


		void UploadUniformInt(const std::string& name, const int value);
		void UploadUniformInt2(const std::string& name, const glm::ivec2 ivec);

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