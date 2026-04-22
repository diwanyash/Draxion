#include "DraxionMain.h"
#include "Layers/ExampleLayer.h"
#include "Layers/TestLayer.h"

class Sandbox : public Draxion::Application
{
public:
	Sandbox()
	{
		LOG_CLIENT_TRACE("SandBox Constructed");
		PushLayer(new Draxion::ExampleLayer() );
		PushLayer(new Draxion::TestLayer() );
	}
	~Sandbox()
	{
		LOG_CLIENT_TRACE("SandBox Destroyed");
	}
};

Draxion::Application* Draxion::CreateApplication()
{
	return new Sandbox();
}

