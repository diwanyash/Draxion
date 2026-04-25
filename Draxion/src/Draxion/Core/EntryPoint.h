#pragma once
#include "Core.h"
#include "Logger.h"
#include "Application.h"

extern Draxion::Application* Draxion::CreateApplication();

int main( int argc, char** argv )
{
	Draxion::Logger::Init();

	LOG_CLIENT_TRACE("Initialized EntryPoint");

	Draxion::Application* app = Draxion::CreateApplication();
	
	app->Run();
	delete app;

	return 0;
}
