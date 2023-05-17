export module log;

//#include "spdlog/spdlog.h"
//import "log.h";
import <string>;

namespace Log
{
	//enum LogType { Standard, Test };

	//struct LogData
	//{
	//	static const std::string	pattern;
	//	static const std::string	testPattern;
	//	static bool					setUp;
	//	static LogType				logType;
	//	//static std::shared_ptr < spdlog::logger> ;
	//};

	//bool LogData::setUp = false;
	//const std::string LogData::pattern = "[testlogger][error(red)][%H:%M:%S %z] [thread %t] %v";
	//const std::string LogData::pattern = "[%^info(green)%$] Some message";
	//const std::string LogData::pattern = "[%!]%^%v%$";
	//const std::string LogData::testPattern = "[%!]%^%v%$";

	/*void SetupLogger()
	{
		if (LogData::setUp)
			return;

		spdlog::set_pattern(LogData::testPattern);
	}*/

	export void error(std::string message)
	{
		//SetupLogger();
		//spdlog::error("{}", message);
	}

	/*static void info(std::string message)
	{
		SetupLogger();
		spdlog::info("{}", message);
	}*/
}