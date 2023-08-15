#pragma once

#include "Core.h"
#include "Core/Timestep.h"
#include "LayerStack.h"
#include "Events/WindowEvent.h"
#include "Events/ApplicationEvent.h"
#include "Log.h"
#include "Window.h"

#include "Artifax/ImGui/ImGuiLayer.h"

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
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		inline Window& GetWindow() const { return *m_Window; }
	public:
		inline static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(Events::WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		LayerStack m_LayerStack;
		bool m_Running{ true };
		float m_LastFrameTime{0};

		unsigned int m_VertexArray, m_VertexBuffer, m_IndexBuffer;
	private:
		static Application* s_Instance;
	};

	//To be define in client
	Application* CreateApplication();
}

