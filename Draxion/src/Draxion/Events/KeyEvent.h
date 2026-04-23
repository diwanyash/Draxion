#pragma once
#include "Event.h"

namespace Draxion
{
	class DRX_API KeyPressedEvent : public Event
	{
	public:
		KeyPressedEvent( int KeyCode)
			:
			m_KeyCode( KeyCode )
		{ }

		int GetKeyCode() const { return m_KeyCode; }

		const char* GetName() const override { return "KeyPressed"; }
	private:
		int m_KeyCode;
	};

	class DRX_API KeyReleasedEvent : public Event
	{
	public:
		KeyReleasedEvent(int KeyCode)
			:
			m_KeyCode(KeyCode)
		{
		}

		int GetKeyCode() const { return m_KeyCode; }

		const char* GetName() const override { return "KeyReleased"; }
	private:
		int m_KeyCode;
	};
}