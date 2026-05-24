#pragma once
#include "Core.h"
#include <iostream>

namespace Draxion
{
	class DRX_API Logger
	{
	public:
		static void Init();
		static const char* GetTime();
	private:
		static char buffer[9];
	};
}

#define DX_COLOR_RED     "\033[31m"
#define DX_COLOR_GREEN   "\033[32m"
#define DX_COLOR_YELLOW  "\033[33m"
#define DX_COLOR_BLUE    "\033[34m"
#define DX_FATAL_COLOR   "\033[41;97m"
#define DX_COLOR_RESET   "\033[0m"

// ENGINE LOGS
#define LOG_ENGINE_TRACE(x) std::cout << "[" << Draxion::Logger::GetTime() << "] Engine:: > " << x << "\n";
#define LOG_ENGINE_INFO(x)  std::cout << DX_COLOR_GREEN  << "[" << Draxion::Logger::GetTime() << "] Engine:: > " << x << DX_COLOR_RESET << "\n";
#define LOG_ENGINE_WARN(x)  std::cout << DX_COLOR_YELLOW << "[" << Draxion::Logger::GetTime() << "] Engine:: > " << x << DX_COLOR_RESET << "\n";
#define LOG_ENGINE_ERROR(x) std::cout << DX_COLOR_RED    << "[" << Draxion::Logger::GetTime() << "] Engine:: > " << x << DX_COLOR_RESET << "\n";
#define LOG_ENGINE_FATAL(x) std::cout << DX_FATAL_COLOR  << "[" << Draxion::Logger::GetTime() << "] Engine:: > " << x << DX_COLOR_RESET << "\n";


// CLIENT LOGS
#define LOG_CLIENT_TRACE(x) std::cout << "[" << Draxion::Logger::GetTime() << "] Client:: > " << x << "\n";
#define LOG_CLIENT_INFO(x)  std::cout << DX_COLOR_GREEN  << "[" << Draxion::Logger::GetTime() << "] Client:: > " << x << DX_COLOR_RESET << "\n";
#define LOG_CLIENT_WARN(x) do { \
    const char* t = Draxion::Logger::GetTime(); \
    std::cout << DX_COLOR_YELLOW << "[" << t << "] Engine:: > " << x << DX_COLOR_RESET << "\n"; \
} while(0)
//#define LOG_CLIENT_WARN(x)  std::cout << DX_COLOR_YELLOW << "[" << Draxion::Logger::GetTime() << "] Client:: > " << x << DX_COLOR_RESET << "\n";
#define LOG_CLIENT_ERROR(x) std::cout << DX_COLOR_RED    << "[" << Draxion::Logger::GetTime() << "] Client:: > " << x << DX_COLOR_RESET << "\n";
#define LOG_CLIENT_FATAL(x) std::cout << DX_FATAL_COLOR  << "[" << Draxion::Logger::GetTime() << "] Client:: > " << x << DX_COLOR_RESET << "\n";