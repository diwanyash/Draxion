#include "DraxionMain.h"

class Sandbox : public Draxion::Application
{
public:
	Sandbox()
	{
		LOG_CLIENT_TRACE("SandBox Constructed");
	}
	void OnUpdate() override
	{
		//if (Draxion::Input::IsKeyPressed(Draxion::Key::W))
		//{
		//	LOG_CLIENT_TRACE("W is Pressed");
		//}
		if (Draxion::Input::IsMouseButtonPressed(Draxion::Key::MOUSE_BUTTON_LEFT))
		{
			LOG_CLIENT_TRACE("{" << Draxion::Input::GetMousePosition().first << "," << (int)(Draxion::Input::GetMousePosition().second) << "}");
		}
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

