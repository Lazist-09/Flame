#pragma once



#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"



namespace Flame {

	class FL_API Log
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

#define FL_CORE_TRACE(...)	::Flame::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define FL_CORE_INFO(...)	::Flame::Log::GetCoreLogger()->info(__VA_ARGS__)
#define FL_CORE_WARN(...)	::Flame::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define FL_CORE_ERROR(...)	::Flame::Log::GetCoreLogger()->error(__VA_ARGS__)
#define FL_CORE_FATAL(...)	::Flame::Log::GetCoreLogger()->critical(__VA_ARGS__)

#define FL_CLIENT_TRACE(...)	::Flame::Log::GetClientLogger()->trace(__VA_ARGS__)
#define FL_CLIENT_INFO(...)	    ::Flame::Log::GetClientLogger()->info(__VA_ARGS__)
#define FL_CLIENT_WARN(...)  	::Flame::Log::GetClientLogger()->warn(__VA_ARGS__)
#define FL_CLIENT_ERROR(...)	::Flame::Log::GetClientLogger()->error(__VA_ARGS__)
#define FL_CLIENT_FATAL(...)	::Flame::Log::GetClientLogger()->critical(__VA_ARGS__)	