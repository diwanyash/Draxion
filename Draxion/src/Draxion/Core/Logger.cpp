#include "Logger.h"
#include <iomanip>
#include <chrono>


namespace Draxion
{
	void Logger::Init()
	{
		std::cout << "Logger Inisilized\n";
	}
	std::string Logger::GetTime()
	{
		auto now = std::chrono::system_clock::now();
		auto time = std::chrono::system_clock::to_time_t(now);

		std::tm bt{};
		localtime_s(&bt, &time);

		char buffer[9];
		sprintf_s(buffer, "%02d:%02d:%02d", bt.tm_hour, bt.tm_min, bt.tm_sec);

		return std::string(buffer);
	}
}