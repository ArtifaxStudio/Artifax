#include "axpch.h"
#include "LayerStack.h"

namespace Artifax
{
	LayerStack::LayerStack()
	{
		
	}
	LayerStack::~LayerStack()
	{
		for each (Layer* layer in m_Layers)
		{
			delete layer;
		}
	}
	void LayerStack::PushLayer(Layer* layer)
	{
		m_Layers.emplace(m_Layers.begin()  + m_LayersInsertIndex, layer);
		m_LayersInsertIndex++;
		layer->OnAttach();
	}
	void LayerStack::PushOverlayLayer(Layer* overlay)
	{
		m_Layers.emplace_back(overlay);
		overlay->OnAttach();
	}
	void LayerStack::PopLayer(Layer* layer)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);

		if (it == m_Layers.end()) return;

		m_Layers.erase(it);
		m_LayersInsertIndex--;
		layer->OnDetach();
	}
	void LayerStack::PopOverlayLayer(Layer* overlay)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);

		if (it == m_Layers.end()) return;

		m_Layers.erase(it);
		overlay->OnDetach();
	}
}
