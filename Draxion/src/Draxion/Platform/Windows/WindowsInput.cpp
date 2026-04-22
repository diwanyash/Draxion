#include "WindowsInput.h"
#include <GLFW/glfw3.h>
#include "../../Core/Application.h"
#include "../Windows/Window.h"

namespace Draxion
{
	bool WindowsInput::IsKeyPressedImpl(int keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		int state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS;
	}
	bool WindowsInput::IsMouseButtonPressedImpl(int Button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		return glfwGetMouseButton( window, Button ) == GLFW_PRESS;
	}
	std::pair<float, float> WindowsInput::GetMousePositionImpl()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

		double x, y;
		glfwGetCursorPos( window, &x, &y );

		return { (float)x,(float)y };
	}
}
