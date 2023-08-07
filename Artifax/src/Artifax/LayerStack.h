#pragma once

#include "Artifax/Core.h"
#include "Layer.h"

#include <vector>

namespace Artifax
{
	class LayerStack
	{
		typedef std::vector<Layer*> layersContainer;
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlayLayer(Layer* overlay);
		/// <summary>
		/// Pop doesn't delete the layer from memory, so a Poped layer could be repushed without problems
		/// </summary>
		/// <param name="layer"></param>
		void PopLayer(Layer* layer);
		/// <summary>
		/// Pop doesn't delete the layer from memory, so a Poped layer could be repushed without problems
		/// </summary>
		/// <param name="overlay"></param>
		void PopOverlayLayer(Layer* overlay);

		layersContainer::iterator begin() { return m_Layers.begin(); }
		layersContainer::iterator end() { return m_Layers.end(); }
	private:
		layersContainer m_Layers;
		layersContainer::iterator m_LayersInsert;
	};
}

