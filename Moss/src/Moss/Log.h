#pragma once


#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Moss {

	class MOSS_API Log
	{
	public:

		static void Init();
		inline static std::shared_ptr<spdlog::logger>&GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>&GetClientLogger() { return s_ClientLogger; }

	private:

		static std::shared_ptr<spdlog::logger> s_ClientLogger;
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
	};
}

//Core log macros
#define MS_CORE_ERROR(...) ::Moss::Log::GetCoreLogger()->error(__VA_ARGS__)
#define MS_CORE_WARN(...) ::Moss::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define MS_CORE_INFO(...) ::Moss::Log::GetCoreLogger()->info(__VA_ARGS__)
#define MS_CORE_TRACE(...) ::Moss::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define MS_CORE_FATAL(...) ::Moss::Log::GetCoreLogger()->fatal(__VA_ARGS__)
//#define MS_CORE_ASSERT(...) ::Moss::Log::GetCoreLogger()->assert(__VA_ARGS__)

//Client log macros
#define MS_ERROR(...) ::Moss::Log::GetClientLogger()->error(__VA_ARGS__)
#define MS_WARN(...) ::Moss::Log::GetClientLogger()->warn(__VA_ARGS__)
#define MS_INFO(...) ::Moss::Log::GetClientLogger()->info(__VA_ARGS__)
#define MS_TRACE(...) ::Moss::Log::GetClientLogger()->trace(__VA_ARGS__)
#define MS_FATAL(...) ::Moss::Log::GetClientLogger()->fatal(__VA_ARGS__)

