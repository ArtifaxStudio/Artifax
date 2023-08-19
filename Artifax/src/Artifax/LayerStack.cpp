#include "axpch.h"
#include "LayerStack.h"

namespace Artifax
{
	LayerStack::LayerStack()
	{
		AX_PROFILE_FUNCTION();

	}
	LayerStack::~LayerStack()
	{
		AX_PROFILE_FUNCTION();

		for each (Layer* layer in m_Layers)
		{
			delete layer;
		}
	}
	void LayerStack::PushLayer(Layer* layer)
	{
		AX_PROFILE_FUNCTION();

		m_Layers.emplace(m_Layers.begin()  + m_LayersInsertIndex, layer);
		m_LayersInsertIndex++;
		layer->OnAttach();
	}
	void LayerStack::PushOverlayLayer(Layer* overlay)
	{
		AX_PROFILE_FUNCTION();

		m_Layers.emplace_back(overlay);
		overlay->OnAttach();
	}
	void LayerStack::PopLayer(Layer* layer)
	{
		AX_PROFILE_FUNCTION();

		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);

		if (it == m_Layers.end()) return;

		m_Layers.erase(it);
		m_LayersInsertIndex--;
		layer->OnDetach();
	}
	void LayerStack::PopOverlayLayer(Layer* overlay)
	{
		AX_PROFILE_FUNCTION();

		auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);

		if (it == m_Layers.end()) return;

		m_Layers.erase(it);
		overlay->OnDetach();
	}
}
