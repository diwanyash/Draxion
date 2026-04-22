#pragma once
#include <string>

namespace Draxion
{
	class Window
	{
	public:
		virtual ~Window() = default;

		virtual void OnUpdate() = 0;
		virtual bool ShouldClose() = 0;
		virtual void SetShouldClose( bool flag ) = 0;
		virtual void* GetNativeWindow() const = 0;

		static Window* CreateWindow( unsigned int Width, unsigned int Height, const std::string& title );

	};
}