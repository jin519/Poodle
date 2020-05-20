#pragma once

#include <string>

namespace GLCore
{
	class TextReader abstract
	{
	public:
		static std::string read(const std::string_view& path);
	};
}