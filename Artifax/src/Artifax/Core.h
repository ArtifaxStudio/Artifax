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

#if AX_DEBUG
	#define AX_ENABLE_ASSERT
#endif

#ifdef AX_ENABLE_ASSERT
	#define AX_ASSERT(x,...) { if(!(x)) { AX_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
	#ifdef AX_BUILD_DLL
		#define AX_CORE_ASSERT(x,...) { if(!(x)) { AX_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
	#endif
#else
	#define AX_ASSERT(x,...)
	#ifdef AX_BUILD_DLL
		#define AX_CORE_ASSERT(x,...)
	#endif
#endif

#define BIT(x) (1 << x)

#define AX_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
