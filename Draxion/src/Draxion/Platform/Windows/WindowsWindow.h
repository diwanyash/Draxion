#pragma once
#include "Draxion/Core/Core.h"
#include "Draxion/Platform/Windows/Window.h"

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