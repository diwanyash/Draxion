#include "Shader.h"
#include "../../Core/Logger.h"
#include "glad/glad.h"
#include <glm/gtc/type_ptr.hpp>
#include <sstream>
#include <fstream>
#include <string>

namespace Draxion
{
	static unsigned int Compile( unsigned int type, const char* path )
	{
		unsigned int id = glCreateShader(type);

		// Load Shader form file
		std::string Code;
		std::ifstream ShaderFile;

		// exception throwing
		ShaderFile.exceptions( std::ifstream::failbit | std::ifstream::badbit );

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
			LOG_ENGINE_ERROR( stype << " Failed to Compile " << infoLog);
		}

		return id;
	}

	Shader::Shader( const char* vertexShaderPath, const char* fragmentShaderPath )
	{
		m_RendererID = glCreateProgram();

		// compiling
		unsigned int vs = Compile( GL_VERTEX_SHADER, vertexShaderPath);
		unsigned int fs = Compile( GL_FRAGMENT_SHADER, fragmentShaderPath);

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
	Shader::~Shader()
	{
		glDeleteProgram( m_RendererID );
	}
	void Shader::Bind() const
	{
		glUseProgram(m_RendererID);
	}
	void Shader::Unbind() const
	{
		glUseProgram(0);
	}

	void Shader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
	{
		unsigned int location = glGetUniformLocation( m_RendererID, name.c_str() );
		glUniformMatrix4fv( location, 1, GL_FALSE, glm::value_ptr(matrix) );
	}

}
