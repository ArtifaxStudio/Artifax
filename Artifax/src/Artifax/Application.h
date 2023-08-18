#pragma once

#include "Artifax/Core.h"
#include "Artifax/Core/Timestep.h"
#include "Artifax/LayerStack.h"
#include "Artifax/Events/WindowEvent.h"
#include "Artifax/Events/ApplicationEvent.h"
#include "Artifax/Log.h"
#include "Artifax/Window.h"

#include "Artifax/Renderer/Renderer.h"
#include "Artifax/Input.h"

#include "Artifax/ImGui/ImGuiLayer.h"

#include "Artifax/Renderer/Shader.h"
#include "Artifax/Renderer/Buffer.h"
#include "Artifax/Renderer/VertexArray.h"

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

		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<VertexArray> m_VertexArray;

		std::shared_ptr<Shader> m_BlueShader;
		std::shared_ptr<VertexArray> m_SquareVA;
	private:
		static Application* s_Instance;
	};

	//To be define in client
	Application* CreateApplication();
}

