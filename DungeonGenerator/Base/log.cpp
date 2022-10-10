#include "log.h"

namespace Log
{
	bool LogData::setUp = false;
	//const std::string LogData::pattern = "[testlogger][error(red)][%H:%M:%S %z] [thread %t] %v";
	//const std::string LogData::pattern = "[%^info(green)%$] Some message";
	//const std::string LogData::pattern = "[%!]%^%v%$";
	const std::string LogData::testPattern = "[%!]%^%v%$";
}