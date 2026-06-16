#pragma once
#include "Core.h"
#include "Logger.h"
#include "Application.h"
#include "Draxion/Debug/Profiler/Profiler.h"

#include <iostream>

extern Draxion::Application* Draxion::CreateApplication();

int main( int argc, char** argv )
{
	Draxion::Profiler::Get().BeginSession("DraxionProfile.json");
	Draxion::Logger::Init();

	LOG_CLIENT_TRACE("Initialized EntryPoint");

	Draxion::Application* app = Draxion::CreateApplication();
	
	app->Run();
	delete app;

	Draxion::Profiler::Get().EndSession();

	return 0;
}
