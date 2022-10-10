#pragma once

#include "spdlog/spdlog.h" //https://github.com/gabime/spdlog


#include <string>

#define SPDLOG_TRACE_ON
#define SPDLOG_LOG_LEVEL  SPDLOG_LEVEL_CRITICAL

//std::shared_ptr < spdlog::logger> log = spdlog::stdout_logger_st("mylogger");
//log->set_level(spdlog::level::trace);
//log->set_pattern("[%!]%^%v%$");
//
//SPDLOG_TRACE(log, "Enabled only #ifdef SPDLOG_TRACE_ON..{} ,{}", 1, 3.23);
//
//log->trace("alma");

namespace Log
{
	enum LogType{Standard, Test};

	struct LogData
	{
		static const std::string	pattern;
		static const std::string	testPattern;
		static bool					setUp;
		static LogType				logType;
		//static std::shared_ptr < spdlog::logger> ;
	};

	static void SetupLogger()
	{
		if (LogData::setUp)
			return;

		spdlog::set_pattern(LogData::testPattern);
	}

	static void error(std::string message)
	{
		SetupLogger();
		spdlog::error("{}", message);
	}

	static void info(std::string message)
	{
		SetupLogger();
		spdlog::info("{}", message);
	}
}