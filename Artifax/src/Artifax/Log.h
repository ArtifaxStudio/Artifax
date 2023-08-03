#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h" //Used to log custom types

namespace Artifax
{
	class ARTIFAX_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

//Core log macros
#define AX_CORE_TRACE(...)		::Artifax::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define AX_CORE_INFO(...)		::Artifax::Log::GetCoreLogger()->info(__VA_ARGS__)
#define AX_CORE_WARN(...)		::Artifax::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define AX_CORE_ERROR(...)		::Artifax::Log::GetCoreLogger()->error(__VA_ARGS__)
#define AX_CORE_CRITICAL(...)	::Artifax::Log::GetCoreLogger()->critical(__VA_ARGS__)
							  
//Client log macros
#define AX_TRACE(...)			::Artifax::Log::GetClientLogger()->trace(__VA_ARGS__)
#define AX_INFO(...)			::Artifax::Log::GetClientLogger()->info(__VA_ARGS__)
#define AX_WARN(...)			::Artifax::Log::GetClientLogger()->warn(__VA_ARGS__)
#define AX_ERROR(...)			::Artifax::Log::GetClientLogger()->error(__VA_ARGS__)
#define AX_CRITICAL(...)		::Artifax::Log::GetClientLogger()->critical(__VA_ARGS__)


