#pragma once
#include "Layer.h"
#include <vector>

namespace Draxion
{
	class LayerStack
	{
	public:
		LayerStack() = default;
		~LayerStack();
		void PushLayer(Layer* Layer);
		void PushOverLay(Layer* OverLay);
		void PopLayer(Layer* iLayer);
		void PopOverLay(Layer* iOverLay);
		std::vector<Layer*>::iterator begin() { return Layers_Vec.begin(); };
		std::vector<Layer*>::iterator end() { return Layers_Vec.end(); };
		Layer* operator[](int i);
	private:
		std::vector<Layer*> Layers_Vec;
		unsigned int LayerInsertIndex = 0;
	};
}