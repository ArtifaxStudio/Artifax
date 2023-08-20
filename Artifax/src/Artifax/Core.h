#pragma once

#include <memory>

#ifdef AX_PLATFORM_WINDOWS
	#if AX_DYNAMIC_LINK
		#ifdef AX_BUILD_DLL
			#define ARTIFAX_API __declspec(dllexport)
		#else
			#define ARTIFAX_API __declspec(dllimport)
		#endif
	#else
		#define ARTIFAX_API
	#endif
#else
	#error "Artifax only support Windows!"
#endif

#if AX_DEBUG
	#define AX_ENABLE_ASSERT
#endif

#ifdef AX_ENABLE_ASSERT
	#define AX_ASSERT(x,...) { if(!(x)) { AX_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
	#define AX_CORE_ASSERT(x,...) { if(!(x)) { AX_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
#else
	#define AX_ASSERT(x,...)
	#define AX_CORE_ASSERT(x,...)
#endif

