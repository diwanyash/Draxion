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
	void LayerStack::PopLayer(Layer* iLayer)
	{
		auto it = std::find(Layers_Vec.begin(), Layers_Vec.end(), iLayer );

		if ( it != Layers_Vec.end() )
		{
			Layers_Vec.erase(it);
			LayerInsertIndex--;
		}
	}
	void LayerStack::PopOverLay(Layer* iOverLay)
	{
		auto it = std::find(Layers_Vec.cbegin(), Layers_Vec.cend(), iOverLay );

		if (it != Layers_Vec.end())
		{
			Layers_Vec.erase(it);
		}
	}
	Layer* LayerStack::operator[](int i)
	{
		return Layers_Vec[i];
	}
}
