#pragma once
#include "Event.h"


namespace Draxion
{
	class DRX_API EventDispatcher
	{
	public:
		EventDispatcher(Event& event)
			:
			m_Event( event )
		{}

		template<typename T, typename F>
		bool Dispatch( const F& func ) 
		{
			if ( T* e = dynamic_cast<T*>(&m_Event) )
			{
				m_Event.Handled = func(*e);
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};
}