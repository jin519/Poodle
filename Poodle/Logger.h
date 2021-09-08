#pragma once

#include <string_view>
#include "SeverityType.h"

namespace Poodle 
{
	class Logger 
	{
	public:
		Logger() = delete; 

		static void commit(
			const SeverityType type, 
			const std::string_view& message);
	};
}