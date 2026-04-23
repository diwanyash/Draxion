#include "RendererCommand.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../Core/Logger.h"

////// LATER TO_BE REMOVED/////////
#include <string>
///////////////////////////////////

namespace Draxion
{
	unsigned int ShaderProgram;
	unsigned int VAO;
	void RendererCommand::Init()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


		////// LATER TO_BE REMOVED/////////

		// Actual Data (Vertices)
		float vertices[]
		{
			-0.5f,-0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // 0
			0.0f , 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // 1
			0.5f ,-0.5f, 0.0f, 0.0f, 0.0f, 1.0f,// 2


			//-0.5f,0.5f, 0.0f,  // 1
			//0.5f,0.5f, 0.0f,   // 2
		};

		// Actual Data (Indices)
		unsigned int indices[]
		{
			0,1,2,
		};

		//glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

		// VAO
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		// Generating Buffer VBO
		unsigned int VBO;
		glGenBuffers(1, &VBO);

		// Generating Buffer EBO
		unsigned int EBO;
		glGenBuffers(1, &EBO);

		// Binding Buffer && Data VBO
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		// Binding Buffer && Data EBO
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		// Setting Vertex Attrib for POS
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)0);
		glEnableVertexAttribArray(0);

		// Setting Vertex Attrib for COLOR
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)12);
		glEnableVertexAttribArray(1);

		// Writing Vertex Shader
		std::string RawVertexSource = R"(
			#version 330 core
			
			layout (location = 0) in vec3 aPos;
			layout (location = 1) in vec3 aColor;
			
			out vec3 OurColor;
			
			void main()
			{
				gl_Position = vec4( aPos.xyz , 1.0 );
				OurColor = aColor;
			}
		)";
		const char* VertexShaderSource = RawVertexSource.c_str();

		// Creating Shader for Run-Time use
		unsigned int VertexShader;
		VertexShader = glCreateShader( GL_VERTEX_SHADER );

		// Attach and Compile(RUNTIME) ShaderString and Shader Object
		glShaderSource( VertexShader, 1, &VertexShaderSource, NULL );
		glCompileShader( VertexShader );

		// ERROR HANDLING
		int success;
		char infoLog[512];
		glGetShaderiv(VertexShader, GL_COMPILE_STATUS, &success);

		if(!success)
		{
			glGetShaderInfoLog(VertexShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

		// Writing Fragment/Pixel Shader
		std::string RawFragmentSource = R"(
		#version 330 core

		in vec3 OurColor;	
		out vec4 FragOut;

		void main()
		{
			FragOut = vec4(OurColor, 1.0f);
		}
		)";
		const char* FragmentShaderSource = RawFragmentSource.c_str();

		// Creating Shader for Run-Time use
		unsigned int FragmentShader;
		FragmentShader = glCreateShader( GL_FRAGMENT_SHADER );

		// Attach and Compile(RUNTIME) ShaderString and Shader Object
		glShaderSource( FragmentShader , 1, &FragmentShaderSource, NULL );
		glCompileShader( FragmentShader );

		// ERROR CHECKING FRAGMENT SHADER
		glGetShaderiv(FragmentShader, GL_COMPILE_STATUS, &success);

		if (!success)
		{
			glGetShaderInfoLog(FragmentShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PIXEL::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

		// SHADER PROGRAM
		ShaderProgram = glCreateProgram();

		// Linking Shaders
		glAttachShader( ShaderProgram, VertexShader );
		glAttachShader( ShaderProgram, FragmentShader );
		glLinkProgram( ShaderProgram );

		// ERROR CHECKING PROGRAM LINKING
		glGetProgramiv( ShaderProgram, GL_LINK_STATUS, &success );
		if ( !success )
		{
			glGetProgramInfoLog( ShaderProgram, 512, NULL, infoLog );
			std::cout << "ERROR::PROGRAM::LINK\n" << infoLog << std::endl;

		}

		// Activate Program
		glUseProgram( ShaderProgram );

		// Delete Shader (AFTER LINKING)
		glDeleteShader( VertexShader );
		glDeleteShader( FragmentShader );

		///////////////////////////////////
	}


	void RendererCommand::SetClearColor( float r, float g, float b, float a )
	{
		glClearColor(r, g, b, a);
	}
	void RendererCommand::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	void RendererCommand::Draw()
	{
		//float TimeValue = glfwGetTime();
		//float GreenValue = (sin(TimeValue) / 2.0f) + 0.5f;
		//int VertexColorLocation = glGetUniformLocation( ShaderProgram, "OurColor");
		glUseProgram(ShaderProgram);
		//glUniform4f( VertexColorLocation, 0.0f, GreenValue, 0.0f, 1.0f );
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0 );
	}
}