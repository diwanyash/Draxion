#include "Shader.h"
#include <glad/glad.h>
#include "../../Core/Logger.h"

namespace Draxion
{
	static unsigned int Compile( unsigned int type, const std::string& src )
	{
		unsigned int id = glCreateShader(type);

		// Attach and Compile(RUNTIME) ShaderString and Shader Object
		const char* source = src.c_str();
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

	Shader::Shader( const std::string& vertexShader, const std::string& fragmentShader )
	{
		m_RendererID = glCreateProgram();

		// compiling
		unsigned int vs = Compile( GL_VERTEX_SHADER, vertexShader );
		unsigned int fs = Compile( GL_FRAGMENT_SHADER, fragmentShader );

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

}
