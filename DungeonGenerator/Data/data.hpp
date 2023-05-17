#include <string>
#ifndef DATA_HPP
#define DATA_HPP

#pragma once

namespace Data
{

	class Data
	{

	};


	class PersistentData : public Data
	{
	private:
		

	public:
		void write(std::ostream& os) const
		{
			os << toString();
		}

		virtual std::string toString() const = 0;
		
		//virtual std::string read() = 0;

		virtual ~PersistentData()
		{

		}
	};

}

#endif
