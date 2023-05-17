#include "log.h"

#include "spdlog/spdlog.h" //https://github.com/gabime/spdlog

namespace Log
{
	Logger::Logger(LoggerType type)
	{
		switch (type)
		{
			case LoggerType::Debug:
				spdlog::set_pattern(DebugPattern);
				break;
			case LoggerType::Release:
				spdlog::set_pattern(ReleasePattern);
				break;
			case LoggerType::None:
				spdlog::set_pattern(NonePattern);
				break;
			default:
				spdlog::set_pattern(DebugPattern);
				break;
		}
	}

	void Logger::info(std::string message)
	{
		spdlog::info("{}", message);
	}


	void Logger::error(std::string message)
	{
		spdlog::error("{}", message);
	}

	void Logger::warn(std::string message)
	{
		spdlog::warn("{}", message);
	}
}