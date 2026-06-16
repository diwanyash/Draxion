#include "Profiler.h"

namespace Draxion
{

	void Profiler::WriteProfiler(const ProfileEvent& event)
	{
		std::lock_guard<std::mutex> lock(m_Mutex);

		if (!m_FirstEvent)
			m_Output << ",";

		m_FirstEvent = false;

		m_Output << "{";
		m_Output << "\"cat\":\"function\",";
		m_Output << "\"dur\":" << event.Duration << ",";
		m_Output << "\"name\":\"" << event.Name << "\",";
		m_Output << "\"ph\":\"X\",";
		m_Output << "\"pid\":0,";
		m_Output << "\"tid\":" << event.Thread_ID << ",";
		m_Output << "\"ts\":" << event.Start;

		m_Output << "}";
	}

}
