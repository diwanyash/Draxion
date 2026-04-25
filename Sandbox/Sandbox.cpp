#include "../Draxion/src/Draxion/Core/EntryPoint.h"
#include "DraxionMain.h"
#include "Layers/ExampleLayer.h"

class Sandbox : public Draxion::Application
{
public:
	Sandbox()
	{
		LOG_CLIENT_TRACE("SandBox Constructed"); 
		PushLayer(new Draxion::ExampleLayer() );
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

