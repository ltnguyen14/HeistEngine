#pragma once
#include "Macro.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Heist {
	class Log {
	public:

		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; };
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; };

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

#if !defined(HEIST_DIST_BUILD)
// Core Log Macros
#define HS_CORE_ERROR(...) ::Heist::Log::GetCoreLogger()->error(__VA_ARGS__)
#define HS_CORE_WARN(...)  ::Heist::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define HS_CORE_INFO(...)  ::Heist::Log::GetCoreLogger()->info(__VA_ARGS__)
#define HS_CORE_TRACE(...) ::Heist::Log::GetCoreLogger()->trace(__VA_ARGS__)

// Client Log Macros
#define HS_ERROR(...) ::Heist::Log::GetClientLogger()->error(__VA_ARGS__)
#define HS_WARN(...)  ::Heist::Log::GetClientLogger()->warn(__VA_ARGS__)
#define HS_INFO(...)  ::Heist::Log::GetClientLogger()->info(__VA_ARGS__)
#define HS_TRACE(...) ::Heist::Log::GetClientLogger()->trace(__VA_ARGS__)

#else
// Core Log Macros
#define HS_CORE_ERROR(...) 
#define HS_CORE_WARN(...)  
#define HS_CORE_INFO(...)  
#define HS_CORE_TRACE(...) 

// Client Log Macros
#define HS_ERROR(...) 
#define HS_WARN(...)  
#define HS_INFO(...)  
#define HS_TRACE(...) 
#endif
