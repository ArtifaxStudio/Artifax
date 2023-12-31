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

#ifdef AX_ENABLE_ASSERT
{
	#define AX_ASSERT(x,...) { if(!(x)) { AX_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
	#define AX_CORE_ASSERT(x,...) { if(!(x)) { AX_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
#else
	#define AX_ASSERT(x,...)
	#define AX_CORE_ASSERT(x,...)
#endif

#define BIT(x) (1 << x)
