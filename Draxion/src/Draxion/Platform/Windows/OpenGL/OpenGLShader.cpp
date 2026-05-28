#include "OpenGLShader.h"
#include "Logger.h"
#include "glad/glad.h"
#include <glm/gtc/type_ptr.hpp>
#include <sstream>
#include <fstream>
#include <string>

namespace Draxion
{
	static unsigned int Compile(unsigned int type, const char* path)
	{
		unsigned int id = glCreateShader(type);

		// Load Shader form file
		std::string Code;
		std::ifstream ShaderFile;

		// exception throwing
		ShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try
		{
			ShaderFile.open(path);

			std::stringstream ShaderStream;

			ShaderStream << ShaderFile.rdbuf();

			ShaderFile.close();

			Code = ShaderStream.str();
		}
		catch (std::ifstream::failure e)
		{
			LOG_ENGINE_ERROR("SHADER FILE NOT READ PROPERLY CODE::" << e.code() << "CAUSE::" << e.what());
		}



		// Attach and Compile(RUNTIME) ShaderString and Shader Object
		const char* source = Code.c_str();
		glShaderSource(id, 1, &source, NULL);
		glCompileShader(id);

		// ERROR HANDLING
		int success;
		char infoLog[512];
		glGetShaderiv(id, GL_COMPILE_STATUS, &success);

		if (!success)
		{
			glGetShaderInfoLog(id, 512, NULL, infoLog);
			const char* stype = (id == 0x8B31) ? "GL_VERTEX_SHADER" : "GL_FRAGMENT_SHADER";
			LOG_ENGINE_ERROR(stype << " Failed to Compile " << infoLog);
		}

		return id;
	}

	OpenGLShader::OpenGLShader(const char* vertexShaderPath, const char* fragmentShaderPath)
	{
		m_RendererID = glCreateProgram();

		// compiling
		unsigned int vs = Compile(GL_VERTEX_SHADER, vertexShaderPath);
		unsigned int fs = Compile(GL_FRAGMENT_SHADER, fragmentShaderPath);

		// Linking Shaders
		glAttachShader(m_RendererID, vs);
		glAttachShader(m_RendererID, fs);
		glLinkProgram(m_RendererID);

		// ERROR CHECKING PROGRAM LINKING
		int success;
		char infoLog[512];
		glGetProgramiv(m_RendererID, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(m_RendererID, 512, NULL, infoLog);
			LOG_ENGINE_ERROR("Failed to Link glProgram " << infoLog);
		}

		// Activate Program
		glUseProgram(m_RendererID);

		// Delete Shader (AFTER LINKING)
		glDeleteShader(vs);
		glDeleteShader(fs);
	}
	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererID);
	}
	void OpenGLShader::Bind() const
	{
		glUseProgram(m_RendererID);
	}
	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}

	void OpenGLShader::SetInt(const std::string& name, int value)
	{
		UploadUniformInt(name, value);
	}

	void OpenGLShader::SetInt2(const std::string& name, glm::ivec2 ivec)
	{
		UploadUniformInt2(name, ivec);
	}

	void OpenGLShader::SetInt3(const std::string& name, glm::ivec3 ivec)
	{
		UploadUniformInt3(name, ivec);
	}

	void OpenGLShader::SetInt4(const std::string& name, glm::ivec4 ivec)
	{
		UploadUniformInt4(name, ivec);
	}

	void OpenGLShader::SetFloat(const std::string& name, float value)
	{
		UploadUniformFloat(name, value);
	}

	void OpenGLShader::SetFloat2(const std::string& name, glm::vec2 vec)
	{
		UploadUniformFloat2(name, vec);
	}

	void OpenGLShader::SetFloat3(const std::string& name, glm::vec3 vec)
	{
		UploadUniformFloat3(name, vec);
	}

	void OpenGLShader::SetFloat4(const std::string& name, glm::vec4 vec)
	{
		UploadUniformFloat4(name, vec);
	}

	void OpenGLShader::SetMat3(const std::string& name, glm::mat3 mat)
	{
		UploadUniformMat3(name, mat);
	}

	void OpenGLShader::SetMat4(const std::string& name, glm::mat4 mat)
	{
		UploadUniformMat4(name, mat);
	}

	void OpenGLShader::UploadUniformInt(const std::string& name, const int value)
	{
		unsigned int location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1i(location, value);
	}

	void OpenGLShader::UploadUniformInt2(const std::string& name, const glm::ivec2 ivec)
	{
		unsigned int location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform2i(location, ivec.x, ivec.y);
	}

	void OpenGLShader::UploadUniformInt3(const std::string& name, const glm::ivec3 ivec)
	{
		unsigned int location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform3i(location, ivec.x, ivec.y, ivec.z);
	}

	void OpenGLShader::UploadUniformInt4(const std::string& name, const glm::ivec4 ivec)
	{
		unsigned int location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform4i(location, ivec.x, ivec.y, ivec.z,ivec.w);
	}

	void OpenGLShader::UploadUniformFloat(const std::string& name, const float value)
	{
		unsigned int location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1f(location, value);
	}

	void OpenGLShader::UploadUniformFloat2(const std::string& name, const glm::vec2& vec)
	{
		unsigned int location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform2f(location, vec.x, vec.y);
	}

	void OpenGLShader::UploadUniformFloat3(const std::string& name, const glm::vec3& vec)
	{
		unsigned int location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform3f(location, vec.x, vec.y, vec.z);
	}

	void OpenGLShader::UploadUniformFloat4(const std::string& name, const glm::vec4& vec)
	{
		unsigned int location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform4f(location, vec.x, vec.y, vec.z, vec.w);
	}

	void OpenGLShader::UploadUniformMat3(const std::string& name, const glm::mat3& matrix)
	{
		unsigned int location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
	{
		unsigned int location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

}
