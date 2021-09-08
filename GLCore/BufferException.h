#pragma once

#include <string_view>
#include <exception>

namespace GLCore 
{
	class BufferException : public std::exception
	{
	public:
		BufferException(const std::string_view& message) noexcept;
	};
}