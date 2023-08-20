#pragma once

#ifdef AX_PLATFORM_WINDOWS

extern Artifax::Application* Artifax::CreateApplication();

int main(int argc, char** argv)
{
	Artifax::Log::Init();

	AX_PROFILE_BEGIN_SESSION("Startup", "ArtifaxProfile_Startup.json");
	Artifax::Application* app = Artifax::CreateApplication();
	AX_PROFILE_END_SESSION();

	AX_PROFILE_BEGIN_SESSION("Runtime", "ArtifaxProfile_Runtime.json");
	app->Run();
	AX_PROFILE_END_SESSION();

	AX_PROFILE_BEGIN_SESSION("Shutdown", "ArtifaxProfile_Shutdown.json");
	delete app;
	AX_PROFILE_END_SESSION();
}
#else
#error "Artifax only support Windows!"
#endif