#include <Artifax.h>

class Sandbox : public Artifax::Application
{
public:
	Sandbox()
	{
		PushLayer(new Artifax::ImGuiLayer());
	}

	~Sandbox()
	{

	}
};

Artifax::Application* Artifax::CreateApplication()
{
	return new Sandbox();
}