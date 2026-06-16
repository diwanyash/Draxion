#include "ProfileTimer.h"
#include <thread>

namespace Draxion
{
	void ProfileTimer::Stop()
	{
		auto end = std::chrono::high_resolution_clock::now();

		auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_Start).time_since_epoch().count();
		auto finish = std::chrono::time_point_cast<std::chrono::microseconds>(end).time_since_epoch().count();

		ProfileEvent event;

		event.Name = m_Name;
		event.Start = start;
		event.Duration = finish - start;

		event.Thread_ID = std::hash<std::thread::id>{}(std::this_thread::get_id());

		Profiler::Get().WriteProfiler(event);
	}
}
