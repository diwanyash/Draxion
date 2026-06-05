#include "DraxionMain.h"
#include "Layers/ExampleLayer.h"
#include "Layers/TileLayer.h"
#include "../Draxion/src/Draxion/Core/EntryPoint.h"

class Sandbox : public Draxion::Application
{
public:
	Sandbox()
	{
		LOG_CLIENT_TRACE("SandBox Constructed"); 
		// auto examplelayer = new Draxion::ExampleLayer();
		// PushLayer( examplelayer );
		auto TileSetLayer = new TileLayer();
		PushLayer( TileSetLayer );
		
		// PopOverLay(imguilayer);
		// PopLayer( examplelayer );
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

