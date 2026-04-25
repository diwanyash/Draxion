#pragma once
//#include "Draxion/Core/Core.h"

namespace Draxion
{
	class _declspec(dllexport) Event
	{
	public:
		virtual const char* GetName() const = 0;

		bool Handled = false;
	};
}