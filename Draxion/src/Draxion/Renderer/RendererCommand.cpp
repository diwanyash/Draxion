#include "RendererCommand.h"
#include "Draxion/Platform/Windows/OpenGL/OpenGLRenderAPI.h"

namespace Draxion
{
	RenderAPI* RenderCommand::s_RenderAPI = new OpenGLRenderAPI;
	bool RenderCommand::isWireframe = false;
}