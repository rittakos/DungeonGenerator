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
	enum Platform	{Win, Mac, Independent};

	class Logger // logger interface
	{
	public:

		virtual void info(std::string message) = 0;
		virtual void error(std::string message) = 0;
		virtual void warn(std::string message) = 0;
	};

	class SpdLogger : public Logger // with spdlog
	{
		const std::string DebugPattern		= "[%H:%M:%S]%^%v%$";
		const std::string NonePattern		= "";
		const std::string ReleasePattern	= "[%H:%M:%S]%^%v%$";
	public:
		explicit SpdLogger(LoggerType type);

		virtual void info(std::string message) override;
		virtual void error(std::string message) override;
		virtual void warn(std::string message) override;
	};


	class WinLogger : public Logger // Windows specific logger
	{
	private:
		void*  hConsole;

		const int white = 15;
		const int green = 10;
		const int red = 12;
		const int yellow = 14;

		const int defaultColor = white;
		const int infoColor = green;
		const int errorColor = red;
		const int warningColor = yellow;

	public:
		WinLogger ();

		virtual void info(std::string message) override;
		virtual void error(std::string message) override;
		virtual void warn(std::string message) override;
	};


	static Logger* logger = new WinLogger ();

	static void info(std::string message)
	{
		logger->info(message);
	}

	static void error(std::string message)
	{
		logger->error(message);
	}

	static void warn(std::string message)
	{
		logger->warn(message);
	}
}