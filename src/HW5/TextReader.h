#pragma once

#include <string>

class TextReader abstract
{
public:
	static std::string read(const std::string_view &path);
};