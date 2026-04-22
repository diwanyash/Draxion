#pragma once


namespace Draxion
{
	class Event
	{
	public:
		virtual const char* GetName() const = 0;

		bool Handled = false;
	};
}