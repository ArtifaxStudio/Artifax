#include "axpch.h"

#include "Application.h"

namespace Artifax
{
#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

	Application::Application()
	{
	}

	Application::~Application()
	{
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

	void Application::OnEvent(Events::Event& e)
	{
		Events::EventDispatcher dispatcher(e);
		dispatcher.Dispatch<Events::WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));

		AX_CORE_TRACE("{0}", e);
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PopLayer(Layer* layer)
	{
		m_LayerStack.PopLayer(layer);
	}

	bool Application::OnWindowClose(Events::WindowCloseEvent& e)
	{
		m_Running = false;

		AX_CORE_TRACE("Clossing Window");
		return true;
	}

}