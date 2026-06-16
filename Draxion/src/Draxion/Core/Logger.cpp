#include "Logger.h"
#include <iomanip>
#include <chrono>
#include "Draxion/Debug/Profiler/ProfileTimer.h"

namespace Draxion
{
	char Logger::buffer[] = "";

	void Logger::Init()
	{
		DX_PROFILE_FUNCTION();

		std::ios::sync_with_stdio(false);
		std::cin.tie(nullptr);
		
		std::cout << "Logger Inisilized\n";
	}
	const char* Logger::GetTime()
	{
		DX_PROFILE_FUNCTION();

		auto now = std::chrono::system_clock::now();
		auto time = std::chrono::system_clock::to_time_t(now);

		std::tm bt{};
		localtime_s(&bt, &time);

		sprintf_s(buffer, "%02d:%02d:%02d", bt.tm_hour, bt.tm_min, bt.tm_sec);

		return buffer;
	}
}