#pragma once

#include <string>

namespace GLCore
{
	class TextReader
	{
	public:
		TextReader() = delete;

		static std::string read(const std::string_view& path);
	};
}