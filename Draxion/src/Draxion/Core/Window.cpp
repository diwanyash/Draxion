#include "Window.h"
#include "Draxion/Platform/Windows/WindowsWindow.h"
#include "Draxion/Core/Logger.h"

namespace Draxion
{
	Window* Window::CreateWindow(unsigned int iWidth, unsigned int iHeight, const std::string& title)
	{
		LOG_ENGINE_TRACE("Window CreateWindow");
		return new WindowsWindow( iWidth, iHeight, title );
	}
}