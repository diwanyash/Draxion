#include "Window.h"
#include "WindowsWindow.h"

namespace Draxion
{
	Window* Window::CreateWindow( unsigned int Width, unsigned int Height, const std::string& title )
	{
		return new WindowsWindow( Width, Height, title );
	}
}