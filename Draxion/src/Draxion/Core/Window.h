#pragma once
#include <string>
#include <functional>
#include "Draxion/Events/Event.h"

namespace Draxion
{
	class Window
	{
	public:
		virtual ~Window() = default;

		virtual void OnUpdate() = 0;
		virtual bool ShouldClose() = 0;
		virtual void SetShouldClose( bool flag ) = 0;
		virtual void Init( int width, int height, const std::string& title ) = 0;
		virtual void Shutdown() = 0;
		virtual void* GetNativeWindow() const = 0;
		virtual void SetEventCallback( const std::function<void(Event&)>& callback ) = 0;

		virtual float GetWidth() const = 0;
		virtual float GetHeight() const = 0;

		static Window* CreateWindow( unsigned int Width, unsigned int Height, const std::string& title );
	};
}