#pragma once
#include "../Core/Core.h"
#include <string>
#include <iostream>

namespace Draxion
{
	class DRX_API Logger
	{
	public:
		static void Init();
		static std::string GetTime();

	};
}

// ENGINE LOGS
#define LOG_ENGINE_TRACE(x) std::cout << "[" << Draxion::Logger::GetTime() << "] [Engine::Trace] > " << x << "\n";
#define LOG_ENGINE_WARN(x)  std::cout << "[" << Draxion::Logger::GetTime() << "] [Engine::Warn]  > " << x << "\n";
#define LOG_ENGINE_ERROR(x) std::cout << "[" << Draxion::Logger::GetTime() << "] [Engine::Error] > " << x << "\n";
#define LOG_ENGINE_FATAL(x) std::cout << "[" << Draxion::Logger::GetTime() << "] [Engine::Fatal] > " << x << "\n";


// CLIENT LOGS
#define LOG_CLIENT_TRACE(x) std::cout << "[" << Draxion::Logger::GetTime() << "] [Client::Trace] > " << x << "\n";
#define LOG_CLIENT_WARN(x)  std::cout << "[" << Draxion::Logger::GetTime() << "] [Client::Warn]  > " << x << "\n";
#define LOG_CLIENT_ERROR(x) std::cout << "[" << Draxion::Logger::GetTime() << "] [Client::Error] > " << x << "\n";
#define LOG_CLIENT_FATAL(x) std::cout << "[" << Draxion::Logger::GetTime() << "] [Client::Fatal] > " << x << "\n";