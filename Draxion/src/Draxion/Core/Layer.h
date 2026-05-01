#pragma once
#include "../Events/Event.h"
#include <string>

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
		virtual void OnImGuiRender() {};
		virtual void OnEvent( Event& e ) {}
		void HideLayer()
		{
			IsLayerHidden = true;
		}
		void UnHideLayer()
		{
			// CAN ADD ON UPDATE FUNCTION
			IsLayerHidden = false;
		}
		virtual bool IsHidden() { return IsLayerHidden; };
		inline const std::string& GetName() { return Layer_Name; };
	protected:
		std::string Layer_Name;
	private:
		bool IsLayerHidden = false;
	};
}