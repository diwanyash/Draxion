#pragma once
#include "../Core/Core.h"

namespace Draxion
{
	class DRX_API Event
	{
	public:
		virtual const char* GetName() const = 0;

		bool Handled = false;
	};
}