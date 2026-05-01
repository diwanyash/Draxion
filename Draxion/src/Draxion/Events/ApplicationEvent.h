#pragma once
#include "Event.h"
#include <utility>

namespace Draxion
{

	class WindowsResizeEvent : public Event
	{
	public:
		WindowsResizeEvent( int width, int height )
			:
			m_Width( width ),
			m_Height( height )
		{}

		const char* GetName() const override { return "Window Resized"; }

		inline const int GetWidth() const { return m_Width; }
		inline const int GetHeight() const { return m_Height; }
	private:
		unsigned int m_Width;
		unsigned int m_Height;
	};
}