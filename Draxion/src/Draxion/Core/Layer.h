#pragma once
#include <string>
#include <Events/Event.h>

namespace Draxion
{
	class Layer
	{
	public:
		Layer(const std::string& iLayer_Name)
			:
			Layer_Name(iLayer_Name)
		{}
		virtual ~Layer() = default;

		virtual void OnAttach() {};
		virtual void OnDetach() {};
		virtual void OnUpdate() {};
		virtual void OnEvent( Event& e ) {};
		std::string GetName() { return Layer_Name; };
	protected:
		std::string Layer_Name;
	};
}