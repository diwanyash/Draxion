#pragma once
#include <string>
#include <fstream> 
#include <mutex>

namespace Draxion
{
	struct ProfileEvent
	{
		std::string Name;

		long long Start;
		long long Duration;

		uint32_t Thread_ID;
	};

	class Profiler
	{
	public:

		static Profiler& Get()
		{
			static Profiler instance;
			return instance;
		}

		void BeginSession( const std::string& Filepath )
		{
			m_Output.open(Filepath);

			m_Output << R"({"traceEvents":[)";
			m_FirstEvent = true;
		}

		void EndSession()
		{
			m_Output << "]}";
			m_Output.close();
		}

		void WriteProfiler( const ProfileEvent& event );
	private:
		std::ofstream m_Output;
		bool m_FirstEvent = true;
		std::mutex m_Mutex;
	};
}