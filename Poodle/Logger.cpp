#include "Logger.h"
#include <sstream>
#include <iostream>

using namespace std; 

namespace Poodle 
{
	void Logger::commit(
		const SeverityType type, 
		const string_view& message)
	{
		ostringstream oss; 

		switch (type)
		{
		case SeverityType::INFO:
			oss << "\033[1;36m[INFO] "; 
			break;

		case SeverityType::WARNING:
			oss << "\033[1;33m[WARNING] "; 
			break;

		case SeverityType::ERROR:
			oss << "\033[1;31m[ERROR] "; 
			break;

		case SeverityType::DEBUG:
			oss << "\033[1;30m[DEBUG] "; 
		}

		oss << message; 
		cout << oss.str() << endl;
	}
}