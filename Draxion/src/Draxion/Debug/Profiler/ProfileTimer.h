#pragma once
// UnComment Below line to Start Profiling __~12Mb/Sec__
// #define HZ_PROFILE

#include "Profiler.h"
#include <chrono>

namespace Draxion
{
	class ProfileTimer
	{
	public:
		ProfileTimer( const char* name )
			:
			m_Name(name)
		{
			m_Start = std::chrono::high_resolution_clock::now();
		}
		~ProfileTimer()
		{
			Stop();
		}

		void Stop();
	private:
		const char* m_Name;
		std::chrono::high_resolution_clock::time_point m_Start;
	};
#ifdef HZ_PROFILE
	#define DX_PROFILE_SCOPE(name) Draxion::ProfileTimer timer##__LINE__(name)
	#define DX_PROFILE_FUNCTION() DX_PROFILE_SCOPE(__FUNCTION__)
#else
	#define DX_PROFILE_SCOPE(name)
	#define DX_PROFILE_FUNCTION() 
#endif

}