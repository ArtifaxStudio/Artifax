#pragma once

#ifdef AX_PLATFORM_WINDOWS

extern Artifax::Application* Artifax::CreateApplication();

int main(int argc, char** argv)
{
	Artifax::Log::Init();

	Artifax::Application* app = Artifax::CreateApplication();
	app->Run();
	delete app;
}
#else
#error "Artifax only support Windows!"
#endif