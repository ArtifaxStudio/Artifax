#pragma once

#include "Artifax/Core.h"
#include "Layer.h"

#include <vector>

namespace Artifax
{
	class LayerStack
	{
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

		std::vector<Layer*> ::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*> ::iterator end() { return m_Layers.end(); }
	private:
		std::vector<Layer*>  m_Layers;
		unsigned int m_LayersInsertIndex{0};
	};
}

