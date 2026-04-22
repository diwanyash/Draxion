#pragma once
#include "Event.h"

namespace Draxion
{
	class MouseEvent : public Event
	{
	public:
		MouseEvent( int MouseButton, int xpos, int ypos)
			:
			button(MouseButton),
			x(xpos),
			y(ypos)
		{}
		const char* GetName() const override { return "MouseKey_is_Pressed"; }

		int GetKeyCode() const { return button; };
		int GetXpos() const { return x; };
		int GetYpos() const { return y; };
	private:
		int button;
		int x, y;
	};
}