#include "VertexArray.h"

#include "Draxion/Renderer/Renderer.h"
#include "Draxion/Platform/Windows/OpenGL/OpenGLVertexArray.h"

#include "../../Core/Logger.h"
namespace Draxion
{
	VertexArray* VertexArray::Create()
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
				return new OpenGLVertexArray();
			}
			default:
			{
				LOG_ENGINE_FATAL("Unsupported RenderAPI");
				return nullptr;
			}
		}
	}
}
