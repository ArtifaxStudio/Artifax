#include <Artifax.h>

class ExampleLayer : public Artifax::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate(Artifax::Timestep ts) override
	{
		AX_TRACE("Delta time: {0}s ({1}ms)", ts.GetSeconds(), ts.GetMiliseconds());

		if (Artifax::Input::IsKeyPressed(AX_KEY_TAB))
			AX_TRACE("Tab key is pressed");
	}

	void OnEvent(Artifax::Events::Event& event) override
	{
		if (event.GetEventType() == Artifax::Events::EventType::KeyPressed)
		{
			Artifax::Events::KeyPressedEvent& e = (Artifax::Events::KeyPressedEvent&)event;
			AX_TRACE("{0}", (char)e.GetKeyCode());
		}
	}
};

class Sandbox : public Artifax::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};

Artifax::Application* Artifax::CreateApplication()
{
	return new Sandbox();
}