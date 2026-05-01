#pragma once
#include "Event.h"

namespace Draxion
{
	class DRX_API MouseButtonPressed : public Event
	{
	public:
		MouseButtonPressed( int MouseButton)
			:
			button(MouseButton)
		{}
		const char* GetName() const override { return "MouseKey_is_Pressed"; }

		int GetMouseButton() const { return button; };
	private:
		int button;
	};

	class DRX_API MouseButtonReleased : public Event
	{
	public:
		MouseButtonReleased( int MouseButton)
			:
			button(MouseButton)
		{}
		const char* GetName() const override { return "MouseKey_is_Released"; }

		int GetMouseButton() const { return button; };
	private:
		int button;
	};

	class DRX_API MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(int xOffset, int yOffset)
			:
			xOffset(xOffset),
			yOffset(yOffset)
		{}
		const char* GetName() const override { return "Mouse_Is_Scrolled"; }

		int GetXOffset() const { return xOffset; };
		int GetYOffset() const { return yOffset; };
	private:
		int xOffset, yOffset;
	};

	class DRX_API MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(int ixPos, int iyPos)
			:
			xPos(ixPos),
			yPos(iyPos)
		{
		}
		const char* GetName() const override { return "MouseKey_is_Moved"; }

		int GetXpos() const { return xPos; };						
		int GetYpos() const { return yPos; };						
	private:
		int xPos, yPos;
	};
}