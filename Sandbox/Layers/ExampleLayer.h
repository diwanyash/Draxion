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
			static int count = 0;
			if( ++count % 144 == 0 )
			LOG_ENGINE_TRACE("Example Layer Updated");
		}

		void OnEvent( Event& e ) override
		{
			LOG_ENGINE_TRACE( e.GetName() );
		}
	};
}