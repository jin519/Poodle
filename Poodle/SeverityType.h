#pragma once

namespace Poodle 
{
	enum class SeverityType
	{
		INFO,		// Bright Cyan   \033[1;36m  
		WARNING,	// Bright Yellow \033[1;33m
		ERROR,		// Bright Red	 \033[1;31m
		DEBUG		// Bright Black  \033[1;30m
	};
}