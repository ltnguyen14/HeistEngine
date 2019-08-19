#include "hspch.h"
#include "Log.h"

namespace Heist {
	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	void Log::Init() {
		spdlog::set_pattern("%^[%T] %n: %v%$");
		s_CoreLogger = spdlog::stdout_color_mt("HIEST");
		s_CoreLogger->set_level(spdlog::level::trace);
		HS_CORE_TRACE("Engine Logger Inititated");

		s_ClientLogger = spdlog::stdout_color_mt("APP");
		s_ClientLogger->set_level(spdlog::level::trace);
		HS_TRACE("Client Logger Inititated");
	}
}