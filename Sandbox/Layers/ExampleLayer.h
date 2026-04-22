#pragma once
#include "DraxionMain.h"

namespace Draxion
{
	class ExampleLayer : public Layer
	{
	public:
		ExampleLayer()
			:
			Layer("Example_Layer")
		{}

		void OnAttach() override
		{
			LOG_ENGINE_TRACE("Example Layer Attached");
		}

		void OnDetach() override
		{
			LOG_ENGINE_TRACE("Example Layer Detached");
		}

		void OnUpdate() override
		{
		}

		void OnEvent( Event& e ) override
		{
			//LOG_ENGINE_TRACE( e.GetName() );
			EventDispatcher d(e);

			d.Dispatch<KeyPressedEvent>([](KeyPressedEvent& e)
			{
				if ((e.GetKeyCode()) == Draxion::Key::A)
				{
					LOG_CLIENT_TRACE("Keyboard Event \"A\" Handled by ExampleLayer");
					return true;
				}
				return false;
			});
		}
	};
}