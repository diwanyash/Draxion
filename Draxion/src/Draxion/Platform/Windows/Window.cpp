#include "Window.h"
#include "WindowsWindow.h"
#include "Draxion/Core/Logger.h"

namespace Draxion
{
	Window* Window::CreateWindow(unsigned int Width, unsigned int Height, const std::string& title)
	{
		LOG_ENGINE_TRACE("Window CreateWindow");
		return new WindowsWindow( Width, Height, title );
	}
}