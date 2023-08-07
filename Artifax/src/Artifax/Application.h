#pragma once

#include "Core.h"

#include "LayerStack.h"
#include "Events/Event.h"
#include "Events/WindowEvent.h"
#include "Events/ApplicationEvent.h"
#include "Log.h"
#include "Window.h"

namespace Artifax
{
	class ARTIFAX_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Events::Event& e);
		void PushLayer(Layer* layer);
		void PopLayer(Layer* layer);
	private:
		bool OnWindowClose(Events::WindowCloseEvent& e);
		std::unique_ptr<Window> m_Window;
		LayerStack m_LayerStack;
		bool m_Running = true;
	};

	//To be define in client
	Application* CreateApplication();
}

