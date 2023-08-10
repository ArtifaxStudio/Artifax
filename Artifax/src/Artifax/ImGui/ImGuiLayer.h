#pragma once

#include "Artifax/Layer.h"
#include <Artifax/Events/Event.h>
#include <Artifax/Events/WindowEvent.h>
#include <Artifax/Events/KeyEvent.h>
#include <Artifax/Events/MouseEvent.h>

namespace Artifax
{
	class ARTIFAX_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate() override;
		void OnEvent(Events::Event& event) override;

	private:
		bool OnMouseButtonPressedEvent(Events::MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(Events::MouseButtonReleasedEvent& e);
		bool OnMouseMovedEvent(Events::MouseMovedEvent& e);
		bool OnMouseScrolledEvent(Events::MouseScrolledEvent& e);
		bool OnKeyPressedEvent(Events::KeyPressedEvent& e);
		bool OnKeyReleasedEvent(Events::KeyReleasedEvent& e);
		//bool OnKeyTypedEvent(Events::KeyTypedEvent& e);
		bool OnWindowResizeEvent(Events::WindowResizeEvent& e);

	private:
		float m_Time = 0.0f;
	};
}

