#pragma once

#include <string>
#include <iostream>

//#define SPDLOG_TRACE_ON
//#define SPDLOG_LOG_LEVEL  SPDLOG_LEVEL_CRITICAL

//std::shared_ptr < spdlog::logger> log = spdlog::stdout_logger_st("mylogger");
//log->set_level(spdlog::level::trace);
//log->set_pattern("[%!]%^%v%$");
//
//SPDLOG_TRACE(log, "Enabled only #ifdef SPDLOG_TRACE_ON..{} ,{}", 1, 3.23);
//
//log->trace("alma");

namespace Log
{
	enum LoggerType {None, Release, Debug};

	class Logger
	{
		const std::string DebugPattern		= "[%H:%M:%S]%^%v%$";
		const std::string NonePattern		= "";
		const std::string ReleasePattern	= "[%H:%M:%S]%^%v%$";
	public:
		explicit Logger(LoggerType type);

		void info(std::string message);
		void error(std::string message);
		void warn(std::string message);
	};

	static Logger logger(Debug);

	static void info(std::string message)
	{
		logger.info(message);
	}

	static void error(std::string message)
	{
		logger.error(message);
	}

	static void warn(std::string message)
	{
		logger.warn(message);
	}
}