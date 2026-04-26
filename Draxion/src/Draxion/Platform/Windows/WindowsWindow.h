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
		inline void SetEventCallback( const std::function<void(Event&)>& callback) override;
		void* GetNativeWindow() const override;
		struct WindowData
		{
			unsigned int m_Width;
			unsigned int m_Height;
			std::string  m_Title;
			std::function<void(Event&)> EventFn;
		};
	private:
		//unsigned int m_Width;
		//unsigned int m_Height;
		//std::string m_Title;
		//std::function<void(Event&)> EventFn;
		WindowData m_Data;
		GLFWwindow* m_Window;
	};
}