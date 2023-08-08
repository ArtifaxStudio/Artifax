#include "axpch.h"
#include "LayerStack.h"

namespace Artifax
{
	LayerStack::LayerStack()
	{
		m_LayersInsert = m_Layers.begin();
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
		m_LayersInsert = m_Layers.emplace(m_LayersInsert, layer);
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
		m_LayersInsert--;
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
