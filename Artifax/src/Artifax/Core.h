#pragma once

#ifdef AX_PLATFORM_WINDOWS
	#ifdef AX_BUILD_DLL
		#define ARTIFAX_API __declspec(dllexport)
	#else
		#define ARTIFAX_API __declspec(dllimport)
	#endif
#else
	#error "Artifax only support Windows!"
#endif
