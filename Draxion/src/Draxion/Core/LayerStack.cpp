#include "LayerStack.h"

namespace Draxion
{
	LayerStack::~LayerStack()
	{
		for ( auto* layer : Layers_Vec)
		{
			layer->OnDetach();
			delete layer;
		}
	}
	void LayerStack::PushLayer(Layer* iLayer)
	{
		Layers_Vec.emplace( begin() + LayerInsertIndex, iLayer );
		LayerInsertIndex++;
		iLayer->OnAttach();
	}
	void LayerStack::PushOverLay(Layer* iOverLay)
	{
		Layers_Vec.emplace_back( iOverLay );
		iOverLay->OnAttach();
	}
}
