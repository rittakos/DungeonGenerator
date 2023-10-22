#pragma once
#include <optional>
#include <string>
#include <map>

#include "log.h"

namespace Error
{
	enum ErrorType
	{
		NoError,
		Basic
	};

	class Error
	{
		const std::map<const ErrorType, std::string> messages =
													{
														{NoError,	"OK"},
														{Basic,		"Error"}
													};

		const ErrorType type;
		const std::optional<std::string> errorMessage;

		std::string getComposedMessage() const
		{
			std::string message = messages.at(type);
			if (errorMessage.has_value())
			{
				message += ": ";
				message += errorMessage.value();
			}

			return message;
		}
	public:

		static bool LogErrors;

		explicit Error(const ErrorType type = Basic, std::optional<std::string> message = {}) : 
			type(type), errorMessage(message)
		{
			
		}

		void log() const
		{
			if (!LogErrors)
				return;

			std::string logMessage = getComposedMessage();

			if (type == NoError)
				Log::info(logMessage);
			else
				Log::error(logMessage);
		}

		bool operator==(const Error& other) const
		{
			return this->type == other.type;
		}

		bool operator!=(const Error& other) const
		{
			return !(*this == other);
		}

		std::ostream& operator<<(std::ostream& os) const
		{
			os << getComposedMessage() << std::endl;
			return os;
		}


	};

	bool Error::LogErrors = true;
	
	inline Error Ok = Error(NoError);
	inline Error Err = Error(NoError);
}
	
