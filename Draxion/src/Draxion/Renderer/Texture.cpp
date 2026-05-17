#include "Texture.h"
#include <memory>

#include "Draxion/Renderer/Renderer.h"
#include "Draxion/Platform/Windows/OpenGL/OpenGLTexture.h"

namespace Draxion
{
	Ref<Texture2D> Texture2D::Create( const std::string& path)
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
				return std::make_shared<OpenGLTexture2D>(path);
			}
			default:
			{
				LOG_ENGINE_FATAL("Unsupported RenderAPI");
				return nullptr;
			}
		}
	}
}
