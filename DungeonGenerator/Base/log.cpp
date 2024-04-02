#include "log.h"

// #include "spdlog/spdlog.h" //https://github.com/gabime/spdlog

#include <windows.h>

namespace Log // spdlogger can not use because of the compiler
{
	SpdLogger::SpdLogger(const LoggerType type)
	{
		/*switch (type)
		{
			case Debug:
				spdlog::set_pattern(DebugPattern);
				break;
			case Release:
				spdlog::set_pattern(ReleasePattern);
				break;
			case None:
				spdlog::set_pattern(NonePattern);
				break;
			default:
				spdlog::set_pattern(DebugPattern);
				break;
		}*/
	}

	void SpdLogger::info(std::string message)
	{
		//spdlog::info("{}", message);
		std::cout << "--- Info: " << message << std::endl;
	}


	void SpdLogger::error(std::string message)
	{
		//spdlog::error("{}", message);
		std::cout << "!!! Error: " << message << std::endl;
	}

	void SpdLogger::warn(std::string message)
	{
		//spdlog::warn("{}", message);
		std::cout << "+++ Warning: " << message << std::endl;
	}
}

namespace Log // win only logger with manual coloring to replace spdlog library
{
	WinLogger::WinLogger()
	{
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	}

	void WinLogger::info(std::string message)
	{
		SetConsoleTextAttribute(hConsole, infoColor);
		std::cout << "--- Info: " << message << std::endl;
		SetConsoleTextAttribute(hConsole, defaultColor);
	}

	void WinLogger::error(std::string message)
	{
		SetConsoleTextAttribute(hConsole, errorColor);
		std::cout << "!!! Error: " << message << std::endl;
		SetConsoleTextAttribute(hConsole, defaultColor);
	}

	void WinLogger::warn(std::string message)
	{
		SetConsoleTextAttribute(hConsole, warningColor);
		std::cout << "+++ Warning: " << message << std::endl;
		SetConsoleTextAttribute(hConsole, defaultColor);
	}
}