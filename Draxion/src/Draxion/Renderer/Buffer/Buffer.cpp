#include "Buffer.h"
#include "Draxion/Renderer/Renderer.h"
#include "Draxion/Platform/Windows/OpenGL/OpenGLBuffer.h"
#include "Logger.h"

namespace Draxion
{

	VertexBuffer* VertexBuffer::Create(float* vertices, unsigned int size_B)
	{
		switch ( Renderer::GetAPI() )
		{
			case RenderAPI::API::None :
			{
				LOG_ENGINE_WARN( "None RenderAPI was set!" );
				return nullptr;
			}
			case RenderAPI::API::OpenGL :
			{
				return new OpenGLVertexBuffer( vertices, size_B );
			}
			default:
			{
				LOG_ENGINE_FATAL("Unsupported RenderAPI");
				return nullptr;
			}
		}
	}

	IndexBuffer* IndexBuffer::Create(unsigned int* indices, unsigned int count)
	{
		switch (Renderer::GetAPI())
		{
			case RenderAPI::API::None :
			{
				LOG_ENGINE_WARN("None RenderAPI was set!");
				return nullptr;
			}
			case RenderAPI::API::OpenGL :
			{
				return new OpenGLIndexBuffer(indices, count);
			}
			default:
			{
				LOG_ENGINE_FATAL("Unsupported RenderAPI");
				return nullptr;
			}
		}
	}
}