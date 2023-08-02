#pragma once

#ifdef AX_PLATFORM_WINDOWS

extern Artifax::Application* Artifax::CreateApplication();

int main(int argc, char** argv)
{
	Artifax::Log::Init();
	AX_CORE_TRACE("Artifax Log Initialized!");
	int a = 1;
	AX_INFO("Hello! Var={0}", a);

	Artifax::Application* app = Artifax::CreateApplication();
	app->Run();
	delete app;
}
#else
#error "Artifax only support Windows!"
#endif