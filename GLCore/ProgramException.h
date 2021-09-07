#pragma once

#include <string_view>
#include <exception>

namespace GLCore 
{
	class ProgramException : public std::exception 
	{
	public:
		ProgramException(const std::string_view& message) noexcept;
	};
}