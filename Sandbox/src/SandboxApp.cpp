#include <Artifax.h>

class Sandbox : public Artifax::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

Artifax::Application* Artifax::CreateApplication()
{
	return new Sandbox();
}