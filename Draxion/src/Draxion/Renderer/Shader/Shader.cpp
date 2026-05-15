#include "Shader.h"
#include "Logger.h"
#include "Draxion/Renderer/RenderAPI.h"
#include "Draxion/Renderer/Renderer.h"
#include "Draxion/Platform/Windows/OpenGL/OpenGLShader.h"

namespace Draxion
{
	Shader* Shader::Create( const char* vertexShader, const char* fragmentShader )
	{
		switch (Renderer::GetAPI())
		{
		case RenderAPI::API::None:
		{
			LOG_ENGINE_WARN("None RenderAPI was set!");
			return nullptr;
		}
		case RenderAPI::API::OpenGL:
		{
			return new OpenGLShader( vertexShader,  fragmentShader );
		}
		}

		LOG_ENGINE_FATAL("Unsupported RenderAPI");
		return nullptr;
	}
}