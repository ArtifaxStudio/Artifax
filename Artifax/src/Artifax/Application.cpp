#include "axpch.h"

#include "Application.h"

namespace Artifax
{
	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	bool OnCloseWindow(Events::WindowCloseEvent x)
	{
		return true;
	}

	void Application::Run()
	{
		for each (Layer* layer in m_LayerStack)
		{
			layer->OnUpdate();
		}

		AX_CORE_INFO("Application running");

		while (true);
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PopLayer(Layer* layer)
	{
		m_LayerStack.PopLayer(layer);
	}

}