#pragma once
#include "../../Core/Core.h"
#include "../Windows/Window.h"
#include <string>

struct GLFWwindow;

namespace Draxion
{
	class DRX_API WindowsWindow : public Window
	{
	public:
		WindowsWindow( int width, int height,const std::string& title );
		virtual ~WindowsWindow();

		void OnUpdate() override;
		bool ShouldClose() override;
		void SetShouldClose( bool flag ) override;

		void* GetNativeWindow() const override;
	private:
		GLFWwindow* m_Window;
	};
}